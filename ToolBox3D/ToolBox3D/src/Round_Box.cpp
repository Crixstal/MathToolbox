#include "Round_Box.h"

Round_Box::Round_Box(const Vector3& c, const Vector3& s, const Quaternion& q)
{
    center = c;
    size = s;
    quaternion = q;
}

void Round_Box::myDrawRoundBox(Color color)
{
    Capsule caps1({ center.x - 3.0f, center.y + 3.0f, center.z + 3.0f }, { center.x + 3.0f, center.y + 3.0f, center.z + 3.0f }, 1.0f);
    Cylinder cyl1({ center.x + 3.0f, center.y + 3.0f, center.z + 3.0f }, { center.x + 3.0f, center.y - 3.0f, center.z + 3.0f }, 1.0f, true);
    Cylinder cyl2({ center.x - 3.0f, center.y - 3.0f, center.z + 3.0f }, { center.x - 3.0f, center.y + 3.0f, center.z + 3.0f }, 1.0f, true);
    Capsule caps2({ center.x + 3.0f, center.y - 3.0f, center.z + 3.0f }, { center.x - 3.0f, center.y - 3.0f, center.z + 3.0f }, 1.0f);
    
    Capsule caps3({ center.x - 3.0f, center.y + 3.0f, center.z - 3.0f }, { center.x + 3.0f, center.y + 3.0f, center.z - 3.0f }, 1.0f);
    Cylinder cyl3({ center.x + 3.0f, center.y + 3.0f, center.z - 3.0f }, { center.x + 3.0f, center.y - 3.0f, center.z - 3.0f }, 1.0f, true);
    Cylinder cyl4({ center.x - 3.0f, center.y - 3.0f, center.z - 3.0f }, { center.x - 3.0f, center.y + 3.0f, center.z - 3.0f }, 1.0f, true);
    Capsule caps4({ center.x + 3.0f, center.y - 3.0f, center.z - 3.0f }, { center.x - 3.0f, center.y - 3.0f, center.z - 3.0f }, 1.0f);

    Cylinder cyl5({ center.x - 3.0f, center.y + 3.0f, center.z + 3.0f }, { center.x - 3.0f, center.y + 3.0f, center.z - 3.0f }, 1.0f, true);
    Cylinder cyl6({ center.x + 3.0f, center.y + 3.0f, center.z + 3.0f }, { center.x + 3.0f, center.y + 3.0f, center.z - 3.0f }, 1.0f, true);
    Cylinder cyl7({ center.x + 3.0f, center.y - 3.0f, center.z + 3.0f }, { center.x + 3.0f, center.y - 3.0f, center.z - 3.0f }, 1.0f, true);
    Cylinder cyl8({ center.x - 3.0f, center.y - 3.0f, center.z + 3.0f }, { center.x - 3.0f, center.y - 3.0f, center.z - 3.0f }, 1.0f, true);

    //front face
    caps1.myDrawCapsule(color); // up
    cyl1.myDrawCylinder(color); // right
    cyl2.myDrawCylinder(color); // left
    caps2.myDrawCapsule(color); // down
    
    //back face
    caps3.myDrawCapsule(color); // up
    cyl3.myDrawCylinder(color); // right
    cyl4.myDrawCylinder(color); // left
    caps4.myDrawCapsule(color); // down

    cyl5.myDrawCylinder(color);
    cyl6.myDrawCylinder(color);
    cyl7.myDrawCylinder(color);
    cyl8.myDrawCylinder(color);
}