#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>

#include "Miejsce.h"
#include "Type.h"
#include "PlanszaGry.h"
#include "Information.h"
#include "RysowanieEkranu.h"
#include "StartRestart.h"

// Czas pomiędzy kolejnymi krokami gry (w ms)
int Time{500};

// Obiekt planszy
Plansza plansza;

// Bloczki do rysowania planszy
int blocks[amount_height*amount_width]{};
int ilosc{ 0 };

// Tablica z Buttonami, które będą służyć do ustawiania początkowej konfiguracji planszyq
HWND checkboxes[amount_height * amount_width]{};
// Tablica z boolami, która będzie służyć do sprawdzania czy dany checkbox jest zaznaczony
bool checkboxes_state[amount_height * amount_width]{};

// Button, który będzie służyć do rozpoczęcia gry
HWND Enter_Button;
// Button do restartowania gry 
HWND Restart_Button;
// Edit Control do czasu
HWND Time_Edit;
// Bool do sprawdzania czy Edit Control do czasu został już zainicjalizowany
// Potrzebne gdyż podczas tworzenia Edit Control wysyła on wiadomość o treści 0
bool Initialaized{ false };
// Clear Button do usuwania wszystkich bloków z planszy
HWND Clear_Button;

// Text do Edit Control do czasu
HWND Time_Text;

// panel UI i panel z checkboxami
HWND UI_Panel;
HWND Game_Panel;

// ID Enter Button - 65534, ID Restart Button - 65533, ID Time Edit - 65532, ID Timer - 65531, ID Clear Button - 65530
#define ID_ENTER 65534
#define ID_RESTART 65533
#define ID_TIME_EDIT 65532
#define ID_TIMER 65531
#define ID_CLEAR 65530

// Handler Inputów dla głownego okna gry
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    // Handler Inputów
    switch (uMsg) {
        
		// Zamknięcie okna
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        // Rysowanie ekranu
        case WM_PAINT: {

            // Kolory
            HBRUSH tlo = CreateSolidBrush(RGB(0, 0, 0));
			HBRUSH puste = CreateSolidBrush(RGB(255, 255, 255));
            HBRUSH pelne = CreateSolidBrush(RGB(200, 200, 0));

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

			// Funkcja rysująca plansze podczas gdy gra jest uruchomiona
			// Używa RysowanieEkranu.h
            if (GameStarted == true) {
                GamePlaying(hdc, pelne, puste, plansza);
			}

            EndPaint(hwnd, &ps);

            // Usuwa kolory
            DeleteObject(tlo);
            DeleteObject(puste);
            DeleteObject(pelne);

            return 0;
        }
        
		// Inputy z klawiatury
        case WM_KEYDOWN: {
            
            // Wyjscie z programu (ESC)
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
                return 0;
            }
            
			// Rozpoczecie gry (ENTER) - (Używa StartRestart.h)
            else if (wParam == VK_RETURN) {
                // Start Gry (StartRestart.h)
				GameStarted = StartGame(Enter_Button, Restart_Button, Time_Edit, Time_Text, Clear_Button, 
                                            UI_Panel, Game_Panel, checkboxes, &plansza, blocks, ilosc);
                // Ustawienie Timera który wykonuje kolejne kroki gry co określoną ilość czasu (Time)
                SetTimer(hwnd, ID_TIMER, Time, NULL);
                return 0;
            }

            // Restart Gry (R) - (Używa StartRestart.h)
            else if (wParam == 0x52) {
                GameStarted = RestartGame(Enter_Button, Restart_Button, Time_Edit, Time_Text, Clear_Button, 
                                            UI_Panel, Game_Panel, checkboxes, &plansza);

				// Wyłączenie Timera
				KillTimer(hwnd, ID_TIMER);
                return 0;
            }

            // Poruszanie Sie (WSAD) TODO

            else if (wParam == 0x57) { // (W)
                //for (int i = 0;i < amount_width; i++) {
                //    for (int j = 0;j < amount_height;j++) {
                //        RECT rect;
                //        GetWindowRect(checkboxes[(i * amount_height) + j], &rect);
                //        SetWindowPos(checkboxes[(i * amount_height) + j],NULL , rect.left, rect.right - 10, 0, 0, SWP_NOSIZE);
                //    }
                //}
            }
            else if (wParam == 0x53) { // (S)

            }
            else if (wParam == 0x41) { // (A)

            }
            else if (wParam == 0x44) { // (D)

            }

            return 0;
        }

        // Timer, który odpowiada za wykonywanie kolejnych kroków gry
        case WM_TIMER: {
            if (GameStarted == true) {
                plansza.AllNeighbours();
                plansza.AllPlay();
				// plansza.Show();
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        }
        
        // Handler buttonów
        case WM_COMMAND: {
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Input handler dla panelu UI
LRESULT CALLBACK UiProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch(uMsg) {
        // Rysowanie UI na dole ekranu
        case WM_PAINT: {

			HBRUSH tlo = CreateSolidBrush(RGB(200, 200, 200));

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, tlo);

			EndPaint(hwnd, &ps);
			DeleteObject(tlo);

        }
        case WM_COMMAND: {
            // Start Gry (StartRestart.h)
            if (LOWORD(wParam) == ID_ENTER) {
                GameStarted = StartGame(Enter_Button, Restart_Button, Time_Edit, Time_Text, Clear_Button,
                                            UI_Panel, Game_Panel, checkboxes, &plansza, blocks, ilosc);
                // Ustawienie Timera który wykonuje kolejne kroki gry co określoną ilość czasu (Time)
                SetTimer(GetParent(hwnd), ID_TIMER, Time, NULL);

                SetFocus(GetParent(hwnd));
                return 0;
            }

            // Restart Gry (StartRestart.h)
            else if (LOWORD(wParam) == ID_RESTART) {
                GameStarted = RestartGame(Enter_Button, Restart_Button, Time_Edit, Time_Text, Clear_Button, 
                                            UI_Panel, Game_Panel, checkboxes, &plansza);

				// Wyłączenie Timera
				KillTimer(GetParent(hwnd), ID_TIMER);

                SetFocus(GetParent(hwnd));
                return 0;
            }

			// Zmiana czasu pomiędzy krokami gry
            else if (LOWORD(wParam) == ID_TIME_EDIT && HIWORD(wParam) == EN_CHANGE) {
				
                if (Initialaized == false) {
                    Initialaized = true;
                    return 0;
                }

                char buffer[256];
                GetWindowTextA(Time_Edit, buffer, 256);
                if (atoi(buffer) < 0) {
                    Time = 1;
					SetWindowTextA(Time_Edit, "1");
                }
				Time = atoi(buffer);
                
                return 0;
            }

            // Czyszczenie planszy z bloków
            else if (LOWORD(wParam) == ID_CLEAR) {
                ilosc = 0;
                for (int i{0};i<amount_height*amount_width;i++){
					checkboxes_state[i] = false;
                }
                HWND hChild = GetWindow(GetParent(hwnd), GW_CHILD);
				InvalidateRect(hChild, NULL, FALSE);
                return 0;
            }
        }
	}
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Input handler dla panelu z checkboxami
LRESULT CALLBACK GameProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
        case WM_COMMAND:{
			// Sprawdza czy dany checkbox jest zaznaczony i dodaje go do tablicy blocks
            bool checked = checkboxes_state[LOWORD(wParam)];
            if (checked == true) {
				// Usunięcie bloku z tablicy blocks
				for (int i{ 0 };i < ilosc;i++) {
                    if (blocks[i] == LOWORD(wParam)) {
                        ilosc--;
                        for (int j{ i };j < ilosc;j++) {
                            blocks[j] = blocks[j + 1];
                        }
                        break;
                    }
                }
                checkboxes_state[LOWORD(wParam)] = false;
                InvalidateRect(checkboxes[LOWORD(wParam)], NULL, FALSE);
            }
            else {
				blocks[ilosc] = LOWORD(wParam);
                ilosc++;
                checkboxes_state[LOWORD(wParam)] = true;
                InvalidateRect(checkboxes[LOWORD(wParam)], NULL, FALSE);
            }
            SetFocus(GetParent(hwnd));
            return 0;
	    }
		// Rysowanie obiektów BS_OWNERDRAW w tym przypadku checkboxów
        case WM_DRAWITEM: {

            HBRUSH puste = CreateSolidBrush(RGB(255, 255, 255));
            HBRUSH pelne = CreateSolidBrush(RGB(200, 200, 0));

            DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
            if (checkboxes_state[dis->CtlID] == true) {
                FillRect(dis->hDC, &dis->rcItem, pelne);
            }
            else {
                FillRect(dis->hDC, &dis->rcItem, puste);
            }

            DeleteObject(puste);
            DeleteObject(pelne);

            return TRUE;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    // Tworzenie konsolki obok okna (DEBUG)
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    const wchar_t nazwa[] = L"GameOfLife";
    const wchar_t UI_nazwa[] = L"UI";
    const wchar_t Game_nazwa[] = L"Game";

	// tworzy blueprint klasy okna który jest potem używany do stworzenia okna
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = nazwa;
    RegisterClass(&wc);

    // tworzy blueprint klasy okna UI który jest potem używany do stworzenia Panelu UI
    WNDCLASS ui = { };
    ui.lpfnWndProc = UiProc;
    ui.hInstance = hInstance;
    ui.lpszClassName = UI_nazwa;
    RegisterClass(&ui);

	// tworzy blueprint klasy okna Gry który jest potem używany do stworzenia Panelu z checkboxami
    WNDCLASS gm = { };
    gm.lpfnWndProc = GameProc;
    gm.hInstance = hInstance;
    gm.lpszClassName = Game_nazwa;
    RegisterClass(&gm);

    // Tworzenie głownego okna
    HWND hwnd = CreateWindowEx(
        0,
        nazwa,
        L"GameOfLife",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        60, 0, width, height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

	// Tworzenie panelu UI i panelu z checkboxami
    Game_Panel = CreateWindowEx(
        0,
        Game_nazwa,
        NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0, width, height - 200,
        hwnd,
        NULL,
        hInstance,
        NULL
    );
    UI_Panel = CreateWindowEx(
        0,
        UI_nazwa,
        NULL,
        WS_CHILD | WS_VISIBLE,
        0, height - 200, width, 200,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    // UI -----------------------------------
    // Tworzenie Enter Buttona
    Enter_Button = CreateWindowEx(
        0,
        L"BUTTON",
        L"Start",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        width - 300, 30, 200, 100,
        UI_Panel,
        (HMENU)ID_ENTER,
        hInstance,
        NULL
    );
    // Tworzenie Restart Buttona
    Restart_Button = CreateWindowEx(
        0,
        L"BUTTON",
        L"Restart",
        SW_HIDE | WS_CHILD | BS_PUSHBUTTON,
        width - 150, 40, 75, 75,
        UI_Panel,
        (HMENU)ID_RESTART,
        hInstance,
        NULL
    );
    // Tworzenie Edit Control do czasu
    Time_Edit = CreateWindowEx(
        0,
        L"EDIT",
        L"500",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_CENTER,
        width - 450, 75, 100, 20,
        UI_Panel,
        (HMENU)ID_TIME_EDIT,
        hInstance,
        NULL
    );
    // Tworzenie Texta do Edit Control do czasu
    Time_Text = CreateWindowEx(
        0,
        L"STATIC",
        L"Time (ms):",
        WS_VISIBLE | WS_CHILD | ES_CENTER,
        width - 450, 50, 100, 20,
        UI_Panel,
        NULL,
        hInstance,
        NULL
    );
    // Tworzenie Edit Control do czasu
    Clear_Button = CreateWindowEx(
        0,
        L"BUTTON",
        L"Clear",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        width - 550, 40, 75, 75,
        UI_Panel,
        (HMENU)ID_CLEAR,
        hInstance,
        NULL
    );


	// Tworzenie Checkboxów
    for (int i = 0;i < amount_width; i++) {
        for (int j = 0;j < amount_height;j++) {
            HWND checkbox = CreateWindowEx(
                0,
                L"BUTTON",
                L"",
                WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                 block_width * (i), block_height * (j), block_width, block_height,
                //0, 0, block_width, block_height,
                Game_Panel,
                (HMENU)((i * amount_height) + j),
                hInstance,
                NULL
            );
            checkboxes[(i * amount_height) + j] = checkbox;
            checkboxes_state[(i * amount_height) + j] = false;
        }
    }
    

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

	// Pętla wiadomości która odpowiada za odbieranie inputów
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
}
