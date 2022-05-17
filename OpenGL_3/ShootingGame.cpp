//功能需求計分
//(8 %)操控與背景部分​

//Yes--(1 %) 滑鼠可以控制戰鬥機的左右移動​

//--(1 %) 戰鬥機傭有防禦裝置，並以父子關係方式呈現​

//--(1 %) 可以發射飛彈​

//--(3 %) 能提供連續發射(LINKED LIST，自己撰寫，使用STL 2分)​

//--(2 %)  能產生有速度感的背景物件，或是其他裝飾性的物件​

//(11 %) 敵人部分​

//--(2 %)  有至少三種以上不同外形的敵人(不同的顏色)，基本的四方型不算在內​

//--(3 %) 以物件導向的多型來控制所有的敵人​

//--(1 %)  敵人可以不斷的產生，而且具有不同的顏色​

//--(1 %)  敵人能隨機朝向玩家發射子彈攻擊​

//--(2 %)  戰鬥機發射的子彈可以打到敵人，而且敵人會消失​

//--(2 %)  有 BOSS 級的敵人，且至會根據被攻擊的多寡至少三種不同的狀態(外型改變或攻擊方式)可以切換​

//(4 %) (玩家部分)​

//--(2 %)  能判斷玩家是否被打中 並做出合理的反應​

//--(2 %)  玩家的船艦至少有三種狀態(外型改變)，且有提供玩家的船艦可改變狀態的機制​

//(8 %) 其他你覺得可以展示的技術，包含物理或是數學的運算​

//--(2 %)提供階層式動態控制，並以時間為基礎進行動態的展示​
//(如: OpenGL_2 的 Example4 ，以自動產生的軌跡去控制相關的物件運動)​

//--(2 %)發射導向飛彈攻擊移動的 Boss​

//--敵人被打到有其他的效果​

//--戰鬥機被打到時有其他的效果​

//--背景除了速度感物件外，有其他的效果​

//總計分數:

#include "header/Angel.h"
#include "Common/CSolidSphere.h"
#include "Common/CQuad.h"
#include "Common/CCamera.h"
#include "Common/C2DSprite.h"
#include "Common/CBGStars.h"
#include "Common/CPlayer.h"
#include "Common/CBulletShoot.h"
#include "Common/CCamera.h"
#include "Common/BoundingBox.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 800
#define HALF_SIZE SCREEN_SIZE/2 
#define VP_HALFWIDTH  20.0f
#define VP_HALFHEIGHT 20.0f
#define GRID_SIZE 9 // must be an even number
#define PLAYER_Y_AXIS -5.f

#define NEXT_BULLET_DELAY 0.45f  //0.45f

// For Objects
CBGStars* g_pStars;
CPlayer* g_pPlayer;				// 玩家
CBulletShoot* g_pBullet;				// 子彈
BoundingBox _boundingBox;
float  g_fRQuadT[3] = { 0 };

mat4  mxRT;
mat4  mxBT;
mat4  mxRR;

vec2 vB;

float PlayerScale;

bool g_bStoringAttack;

// For Rotation
GLfloat g_fYAngle = 0;  // Z軸的旋轉角度
GLfloat g_fDir = 1;     // 旋轉方向
bool    m_bAutoRotation = false; // Controlled by Space Key

CSolidSphere* g_pSphere;
CQuad* g_plane;

// For View Point
GLfloat g_fRadius = 8.0;
GLfloat g_fTheta = 45.0f * DegreesToRadians;
GLfloat g_fPhi = 45.0f * DegreesToRadians;

// PassiveMotion
float g_fPTx;		//玩家移動x軸
mat4 g_mxPT;		//玩家座標(g_fPTx, PLAYER_Y_AXIS, 0, 1)
mat4 g_mxPS;		//戰鬥機大小

float g_fcount = 0;
int _playerBulletTime = 400;

//----------------------------------------------------------------------------
// 函式的原型宣告
extern void IdleProcess();

void init(void)
{
	mat4 mxT;
	vec4 vColor;

	point4  eye(0.0f, 0.0f, 50.0f, 1.0f);
	point4  at(0.0f, 0.0f, 0.0f, 1.0f);

	auto camera = CCamera::getInstance();
	camera->updateViewLookAt(eye, at);
	camera->updateOrthographic(-5.0f, 5.0f, -7.0f, 7.0f, 1.0f, 100.0f);

	g_pStars = new CBGStars();
	g_pPlayer = new CPlayer();

	g_pPlayer->setShader();
	vColor.x = 0.2745f; vColor.y = 0.5098f; vColor.z = 0.70588f; vColor.w = 1.0f;
	g_pPlayer->setColor(vColor);
	PlayerScale = g_pPlayer->GetPlayerScale();
	g_mxPS = Scale(PlayerScale, PlayerScale, PlayerScale);	//大小
	g_pPlayer->setBoundingBox(makeBoundingBox(0, 0, -5, 5));
	_boundingBox = g_pPlayer->getBoundingBox();

	g_bStoringAttack = false;

}

//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	g_pStars->GL_Draw();
	g_pPlayer->GL_draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	mat4 mvx, mpx;	// view matrix & projection matrix
	bool bVDirty, bPDirty;	// view 與 projection matrix 是否需要更新給物件
	auto camera = CCamera::getInstance();
	g_fcount += delta;
	g_pPlayer->ShootBullet(delta, g_fPTx, _playerBulletTime);
	g_pStars->UpdateMatrix(delta);
	g_pPlayer->UpdateMatrix(delta);

	// 由上層更新所有要被繪製物件的 View 與 Projection Matrix
	mvx = camera->getViewMatrix(bVDirty);
	if (bVDirty) { // 更新所有物件的 View Matrix
		g_pStars->SetViewMatrix(mvx);
		g_pPlayer->setViewMatrix(mvx);
	}
	mpx = camera->getProjectionMatrix(bPDirty);
	if (bPDirty) { // 更新所有物件的 View Matrix
		g_pStars->SetProjectionMatrix(mpx);
		g_pPlayer->setProjectionMatrix(mpx);
	}
	

	GL_Display();

}

vec2 makeVector(int x, int y)
{
	vec2 V1;
	V1.x = x;
	V1.y = y;
	return V1;
}

//----------------------------------------------------------------------------

void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN);
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 
		if (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		if (state == GLUT_DOWN);
		break;
	default:
		break;
	}
}
// The passive motion callback for a window is called when the mouse moves within the window while no mouse buttons are pressed.
void Win_PassiveMotion(int x, int y) {
	float fsize = 0.006f;
	if (_boundingBox.left <= x <= _boundingBox.right) {
		g_fPTx = fsize * SCREEN_SIZE * (x - HALF_SIZE) / (HALF_SIZE);
		//g_fTy = -fsize*SCREEN_SIZE_Y*(y - HALF_SIZE_Y) / (HALF_SIZE_Y);
		mxRT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);				//位置
		g_pPlayer->GL_SetTranslatMatrix(mxRT);		//更新玩家位置
		g_pPlayer->setTRSMatrix(mxRT* g_mxPS);
	}
	
}

// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	float fsize = 0.006f;
	if (_boundingBox.left <= x <= _boundingBox.right) {
		g_fPTx = fsize * SCREEN_SIZE * (x - HALF_SIZE) / (HALF_SIZE);
		//g_fTy = -fsize*SCREEN_SIZE_Y*(y - HALF_SIZE_Y) / (HALF_SIZE_Y);
		g_mxPT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);				//位置
		g_pPlayer->GL_SetTranslatMatrix(g_mxPT);//更新玩家位置
		g_pPlayer->setTRSMatrix(g_mxPT * g_mxPS);
	}
}

void Win_Keyboard(unsigned char key, int x, int y)
{
	vec4 vColor;
	switch (key) {
	case 'c':
		vColor.x = 0.0f; vColor.y = 0.5098f; vColor.z = 0.1022; vColor.w = 1.0f;
		g_pPlayer->setColor(vColor);
		break;
	case 'x':
		vColor.x = 0.5098f; vColor.y = 0.0f; vColor.z = 0.1022; vColor.w = 1.0f;
		g_pPlayer->setColor(vColor);
		break;
	case 'z':
		vColor.x = 0.2745f; vColor.y = 0.5098f; vColor.z = 0.70588f; vColor.w = 1.0f;
		g_pPlayer->setColor(vColor);
		break;
	case 033:
		if (g_pPlayer != nullptr) delete g_pPlayer;		//玩家
		exit(EXIT_SUCCESS);
		break;
	}
}

void Win_SpecialKeyboard(int key, int x, int y) {
	mat4 rx, ry, rz;
	switch (key) {
	case GLUT_KEY_LEFT:		// 目前按下的是向左方向鍵，移動 Red 往左
		if (g_fRQuadT[0] >= _boundingBox.left) {
			g_fRQuadT[0] -= 0.25;
			mxRT = Translate(g_fRQuadT[0], PLAYER_Y_AXIS, g_fRQuadT[2]);
			g_pPlayer->setTRSMatrix(mxRT * g_mxPS);
		}
		break;
	case GLUT_KEY_RIGHT:		// 目前按下的是向右方向鍵，移動 Red 往右
		if (g_fRQuadT[0] <= _boundingBox.right) {
			g_fRQuadT[0] += 0.25;
			mxRT = Translate(g_fRQuadT[0], PLAYER_Y_AXIS, g_fRQuadT[2]);
			g_pPlayer->setTRSMatrix(mxRT * g_mxPS);
		}
		break;
	case GLUT_KEY_UP:		// 目前按下的是向右方向鍵，移動 Red 往右
		g_fRQuadT[1] += 0.25;
		mxRT = Translate(g_fRQuadT[0], PLAYER_Y_AXIS, g_fRQuadT[2]);
		g_pPlayer->setTRSMatrix(mxRT * g_mxPS);
		break;
	case GLUT_KEY_DOWN:		// 目前按下的是向右方向鍵，移動 Red 往右
		g_fRQuadT[1] -= 0.25;
		mxRT = Translate(g_fRQuadT[0], PLAYER_Y_AXIS, g_fRQuadT[2]);
		g_pPlayer->setTRSMatrix(mxRT * g_mxPS);
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.0666, 0.1176, 0.4235, 1.0); // black background
	glEnable(GL_DEPTH_TEST);
}

//----------------------------------------------------------------------------

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Shooting Game");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMotionFunc(Win_MouseMotion);
	glutPassiveMotionFunc(Win_PassiveMotion);
	glutKeyboardFunc(Win_Keyboard);
	glutSpecialFunc(Win_SpecialKeyboard);	// 處理 NON-ASCII 按鍵如 F1、Home、方向鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}