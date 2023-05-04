#ifndef CONTROL_H_
#define CONTROL_H_

extern int ynew, xnew, znew;

void onKeyboard(unsigned char key, int x, int y);
void onSpecial(int key, int x, int y);
void onSpecialUp(int key, int x, int y);
void onMouse(int button, int state, int x, int y);
void onMotion(int x, int y);
void onKeyboardUp(unsigned char key, int x, int y);

#endif /*CONTROL_H_*/
