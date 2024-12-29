const short Height = 24, Width = 16, PaddingY = 9, PaddingX = 26;
short Speed = 10, LinesCleared = 0, Score = 0, Level = 0, NextPiece, curPiece, NumberOfCustomPolyominos = 0;
unsigned short GameArr[Height + 1] = { 0 }, CustomPolyominos[20 + 1] = { 0 };
unsigned short ClassicTetrominos[7] = { 0b0000011001100000, 0b0100010001000100, 0b0000011000100010, 0b0000011001000100, 0b0000010011100000, 0b0000011000110000, 0b0000001101100000 };
bool isClassic = true, isCustomPolyomino = false;


void gotoyx(int y, int x);
void DrawUI();
void DrawBlock(short block, int pos_y, int pos_x, const char* on_one, const char* on_zero = "\033[2C");
void DrawNextBlock(short blockNext);
void LineCompleteChangeColor(short LineNumber, const char* Color);
void LineCompleteClear(short LineNumber);