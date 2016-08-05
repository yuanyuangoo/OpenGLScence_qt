#ifndef ROAMINGSCENCEMANAGER_H
#define ROAMINGSCENCEMANAGER_H
#include <glm/glm.hpp>
class RoamingScenceManager
{
public:
    RoamingScenceManager();
    ~RoamingScenceManager();

    void init();
    void render();
    void executeRotateOperation(int x, int y);
    void executeScaleOperation(float factor);
    void executeTranslateOperation(int x,int y);
    void getInitPos(int x, int y);
private:
    //辅助坐标系三根轴
    glm::vec3 *AuxX;
	glm::vec3 *AuxY;
	glm::vec3 *AuxZ;

    //旋转后观察点方向与视线向上方向
	glm::vec3 *NewEye;
	glm::vec3 *NewUp;
	glm::vec3 *NewView;

	glm::vec3 *OldMouse;
	glm::vec3 *Mouse;

	glm::vec3 *TempTranslateVec;
    float TempscaleFactor;

    int ID_COORDINATY;
    void init_CoordinaryDisplayList();
};

#endif // ROAMINGSCENCEMANAGER_H
