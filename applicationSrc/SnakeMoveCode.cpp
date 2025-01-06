#include "SnakeMoveCode.hpp"

SnakeMoveCode::SnakeMoveCode(SlidingCubesBlock *host) : SlidingCubesBlockCode(host), module(host) {
    if (not host)
        return;
    addMessageEventFunc2(ELECTFIRST_MSG_ID, std::bind(&SnakeMoveCode::myElectFirstFunc, this, std::placeholders::_1, std::placeholders::_2));
}

void SnakeMoveCode::startup() {
    console << "start " << getId() << "\n";
    if (module->position == goalPosition) return;
    if (isLeader) {
        setColor(RED);
        tryToMove();
    }
}

bool SnakeMoveCode::tryToMove() {
    if (module->position.pt[1] != goalPosition.pt[1])
        return tryToMoveY();
    if (module->position.pt[0] != goalPosition.pt[0])
        return tryToMoveX();

    return false; // Return false if no move conditions are met
}


bool SnakeMoveCode::tryToMoveX() {
    Cell3DPosition position = module->position + Cell3DPosition(0, 1, 0);
    if (module->canMoveTo(position)) {
        module->moveTo(position);
        return true;
    }
    position = module->position + Cell3DPosition(0, 1, 1);
    if (module->canMoveTo(position)) {
        module->moveTo(position);
        return true;
    }
    position = module->position + Cell3DPosition(1, 0, 1);
    if (module->canMoveTo(position)) {
        module->moveTo(position);
        return true;
    }
    return false;
}

bool SnakeMoveCode::tryToMoveY() {
    Cell3DPosition position = module->position + Cell3DPosition(0, 1, 0);
    if (module->canMoveTo(position)) {
        module->moveTo(position);
        return true;
    }
    position = module->position + Cell3DPosition(0, 1, 1);
    if (module->canMoveTo(position)) {
        module->moveTo(position);
        return true;
    }
    position = module->position + Cell3DPosition(0, 1, -1);
    if (module->canMoveTo(position)) {
        module->moveTo(position);
        return true;
    }
    return false;
}

void SnakeMoveCode::myElectFirstFunc(std::shared_ptr<Message> _msg, P2PNetworkInterface *sender) {
    int nbNeighbors = sendMessageToAllNeighbors("ElectFirst", new Message(ELECTFIRST_MSG_ID), 100, 1000, 1, sender);
    if (nbNeighbors) {
        module->setColor(BLUE);
    } else {
        module->setColor(RED);
        tryToMove();
    }
}

void SnakeMoveCode::onMotionEnd() {
    if (module->position == goalPosition) return;
    if (!tryToMove()) {
        module->setColor(YELLOW);
        sendMessageToAllNeighbors("ElectFirst", new Message(ELECTFIRST_MSG_ID), 100, 1000, 1);
    }
}

void SnakeMoveCode::parseUserBlockElements(TiXmlElement *config) {
    const char *attr = config->Attribute("leader");
    isLeader = (attr ? Simulator::extractBoolFromString(attr) : false);
    if (isLeader) {
        std::cout << getId() << " is leader!" << std::endl;
    }
}

void SnakeMoveCode::parseUserElements(TiXmlDocument *config) {
    TiXmlNode *vs = config->FirstChild("vs");
    if (!vs) return;
    TiXmlNode *node = vs->FirstChild("goal");
    if (!node) return;
    TiXmlElement *element = node->ToElement();
    const char *attr = element->Attribute("position");
    if (attr) {
        goalPosition = Simulator::extractCell3DPositionFromString(attr);
        std::cout << "goalPosition = " << goalPosition << std::endl;
    } else {
        goalPosition.set(1, 5, 0);
    }
}

void SnakeMoveCode::onGlDraw() {
    static const float thick = 0.8;
    static const float color[4] = {2.2f, 0.2f, 0.2f, 1.0f};
    const Cell3DPosition &gs = lattice->gridSize;
    const Vector3D gl = lattice->gridScale;
    glDisable(GL_TEXTURE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glNormal3f(0, 0, 1);
    glScalef(gl[0], gl[1], gl[2]);
    glTranslatef(goalPosition[0], goalPosition[1], goalPosition[2] - 0.49);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 36; i++) {
        double cs = 0.5 * cos(i * M_PI / 18);
        double ss = 0.5 * sin(i * M_PI / 18);
        glVertex3f(thick * cs, thick * ss, 0);
        glVertex3f(cs, ss, 0);
    }
    glEnd();
    glPopMatrix();
}