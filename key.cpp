#include <DxLib.h>
#include "key.h"

static unsigned char key[256];
int UpdateKey() {
	char KeyStateBuf[256];
	if (GetHitKeyStateAll(KeyStateBuf) == -1) {
		return -1;
	}
	for (int i = 0; i < 256; i++) {
		if (KeyStateBuf[i] == 1) {
			if (key[i] < CHAR_MAX) {
				key[i]++;
			}
		} else {
			key[i] = 0;
		}
	}
	return 0;
}
int KeyStateOf(int KeyCode) {
	return key[KeyCode];
}
void SetKeyState(int KeyCode, int value) {
	key[KeyCode] = value;
}
