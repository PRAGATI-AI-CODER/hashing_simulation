/* hashhero.c
   HashHero - Animated hashing simulator
   Works with WinBGIm (graphics.h) on modern Windows (Dev-C++ / Code::Blocks).
*/

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>   /* for Beep() and Sleep() */

#define SLOTS 12
#define MAX_KEYS 10

/* compatibility: use Sleep(ms) in place of TurboC delay(ms) */
#define delay(ms) Sleep(ms)

/* simple beep wrapper using Windows Beep (freq in Hz, duration ms) */
void shortBeep(int freq, int t) { Beep(freq, t); }

void playWelcome() {
    shortBeep(880, 70); delay(40);
    shortBeep(1047, 80); delay(40);
    shortBeep(784, 60);
}

void playStep() { shortBeep(900, 20); }
void playCollision() { shortBeep(450, 140); delay(30); shortBeep(350, 90); }
void playSuccess() { shortBeep(1200, 60); delay(30); shortBeep(1400, 90); }

void drawTitle(int sw) {
    char title[] = "HashHero - Interactive Hashing Simulator";
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy((sw - textwidth(title)) / 2, 8, title);
}

void clearPanel(int x, int y, int w, int h) {
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(x, y, x + w, y + h);
}

void showInfo(int panelX, int panelY, int slots, int keys) {
    clearPanel(panelX, panelY, 360, 220);
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(panelX + 10, panelY + 8, "Info & Messages:");
    setcolor(BLACK);
    char buf[100];
    sprintf(buf, "Slots: %d   Keys: %d (max %d)", slots, keys, MAX_KEYS);
    outtextxy(panelX + 10, panelY + 40, buf);
    outtextxy(panelX + 10, panelY + 70, "Linear probing on collision.");
}

void showMessages(const char *a, const char *b, const char *c, int panelX, int panelY) {
    clearPanel(panelX, panelY, 360, 220);
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(panelX + 10, panelY + 8, "Steps / Messages:");
    setcolor(BLACK);
    if (a) outtextxy(panelX + 10, panelY + 40, a);
    if (b) outtextxy(panelX + 10, panelY + 70, b);
    if (c) outtextxy(panelX + 10, panelY + 100, c);
}

void drawTable(int slots, int leftX, int topY, int boxW, int boxH) {
    int i;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (i = 0; i < slots; i++) {
        int x1 = leftX + i * boxW;
        int y1 = topY;
        int x2 = x1 + boxW;
        int y2 = y1 + boxH;
        setcolor(BLUE);
        rectangle(x1, y1, x2, y2);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
        char idx[6];
        sprintf(idx, "%d", i);
        setcolor(WHITE);
        outtextxy(x1 + (boxW - textwidth(idx)) / 2, y2 + 8, idx);
    }
}

void drawPlaced(int table[], int slots, int leftX, int topY, int boxW, int boxH) {
    int i;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (i = 0; i < slots; i++) {
        if (table[i] != -1) {
            int cx = leftX + i * boxW + boxW / 2;
            int cy = topY + boxH / 2;
            char ks[16]; sprintf(ks, "%d", table[i]);
            setcolor(BROWN);
            rectangle(cx - 22, cy - 16, cx + 22, cy + 16);
            setfillstyle(SOLID_FILL, YELLOW);
            bar(cx - 21, cy - 15, cx + 21, cy + 15);
            setcolor(BLACK);
            outtextxy(cx - textwidth(ks)/2, cy - 8, ks);
        }
    }
}

/* simple 2-frame hero mascot */
void drawHero(int frame, int hx, int hy, int key) {
    char kstr[16];
    sprintf(kstr, "%d", key);

    /* body (filled) */
    setcolor(DARKGRAY);
    rectangle(hx - 10, hy - 12, hx + 10, hy + 12);
    setfillstyle(SOLID_FILL, GREEN);
    bar(hx - 9, hy - 11, hx + 9, hy + 11);

    /* head */
    setcolor(GREEN);
    rectangle(hx - 12, hy - 26, hx + 12, hy - 14);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    bar(hx - 11, hy - 25, hx + 11, hy - 15);

    /* legs - alternate for simple walking */
    setcolor(DARKGRAY);
    if (frame == 0) {
        rectangle(hx - 8, hy + 12, hx - 4, hy + 20);
        rectangle(hx + 4, hy + 12, hx + 8, hy + 20);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(hx - 7, hy + 13, hx - 5, hy + 19);
        bar(hx + 5, hy + 13, hx + 7, hy + 19);
    } else {
        rectangle(hx - 8, hy + 12, hx - 2, hy + 20);
        rectangle(hx + 2, hy + 12, hx + 8, hy + 20);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(hx - 7, hy + 13, hx - 3, hy + 19);
        bar(hx + 3, hy + 13, hx + 7, hy + 19);
    }

    /* carried box above head */
    setcolor(BROWN);
    rectangle(hx - 18, hy - 44, hx + 18, hy - 24);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(hx - 17, hy - 43, hx + 17, hy - 25);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(hx - textwidth(kstr)/2, hy - 40, kstr);
}

void flashCell(int x1, int y1, int x2, int y2) {
    int t;
    for (t=0; t<2; t++) {
        setfillstyle(SOLID_FILL, LIGHTRED);
        bar(x1+3, y1+3, x2-3, y2-3);
        delay(120);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        bar(x1+3, y1+3, x2-3, y2-3);
        delay(60);
    }
}

int animateInsert(int table[], int slots, int leftX, int topY, int boxW, int boxH,
                  int panelX, int panelY, int key) {
    int hash = key % slots;
    char s1[120], s2[120], s3[120];
    sprintf(s1, "Key = %d   Hash = %d (key %% %d)", key, hash, slots);
    sprintf(s2, "Hero grabs the number...");
    s3[0] = '\0';

    int sw = getmaxx();
    int heroX = sw / 2;
    int heroY = topY / 2 + 36;
    int frame = 0;
    int destX = leftX + hash * boxW + boxW / 2;

    /* move horizontally above target */
    while (heroX != destX) {
        if (destX > heroX) heroX += 12; else heroX -= 12;
        if ((destX > heroX && heroX > destX) || (destX < heroX && heroX < destX)) heroX = destX;
        cleardevice();
        setbkcolor(LIGHTCYAN);
        drawTitle(sw);
        drawTable(slots, leftX, topY, boxW, boxH);
        drawPlaced(table, slots, leftX, topY, boxW, boxH);
        showMessages(s1, s2, s3, panelX, panelY);
        drawHero(frame, heroX, heroY, key);
        frame = 1 - frame;
        playStep();
        delay(28);
    }

    int idx = hash;
    int tries = 0;
    while (tries < slots) {
        cleardevice();
        setbkcolor(LIGHTCYAN);
        drawTitle(sw);
        drawTable(slots, leftX, topY, boxW, boxH);
        drawPlaced(table, slots, leftX, topY, boxW, boxH);
        sprintf(s2, "Trying index %d", idx);
        showMessages(s1, s2, s3, panelX, panelY);
        drawHero(frame, heroX, heroY, key);
        frame = 1 - frame;
        delay(160);

        if (table[idx] == -1) {
            /* slide down to center of box */
            int finalX = leftX + idx * boxW + boxW / 2;
            int finalY = topY + boxH / 2;
            int hy = heroY;
            while (hy != finalY) {
                if (hy < finalY) hy += 8; else hy -= 8;
                cleardevice();
                setbkcolor(LIGHTCYAN);
                drawTitle(sw);
                drawTable(slots, leftX, topY, boxW, boxH);
                drawPlaced(table, slots, leftX, topY, boxW, boxH);
                sprintf(s2, "Placing at index %d", idx);
                showMessages(s1, s2, s3, panelX, panelY);
                drawHero(frame, finalX, hy, key);
                frame = 1 - frame;
                delay(18);
            }
            table[idx] = key;
            sprintf(s3, "Inserted at index %d", idx);
            cleardevice();
            setbkcolor(LIGHTCYAN);
            drawTitle(sw);
            drawTable(slots, leftX, topY, boxW, boxH);
            drawPlaced(table, slots, leftX, topY, boxW, boxH);
            showMessages(s1, s2, s3, panelX, panelY);
            playSuccess();
            delay(260);
            return idx;
        } else {
            sprintf(s3, "Collision: slot %d has %d", idx, table[idx]);
            cleardevice();
            setbkcolor(LIGHTCYAN);
            drawTitle(sw);
            drawTable(slots, leftX, topY, boxW, boxH);
            drawPlaced(table, slots, leftX, topY, boxW, boxH);
            showMessages(s1, s2, s3, panelX, panelY);

            int fx1 = leftX + idx * boxW;
            int fy1 = topY;
            int fx2 = fx1 + boxW;
            int fy2 = fy1 + boxH;
            flashCell(fx1, fy1, fx2, fy2);
            playCollision();

            /* hero walks to next slot */
            idx = (idx + 1) % slots;
            int nextX = leftX + idx * boxW + boxW/2;
            while (heroX != nextX) {
                if (nextX > heroX) heroX += 10; else heroX -= 10;
                cleardevice();
                setbkcolor(LIGHTCYAN);
                drawTitle(sw);
                drawTable(slots, leftX, topY, boxW, boxH);
                drawPlaced(table, slots, leftX, topY, boxW, boxH);
                sprintf(s2, "Probing to index %d", idx);
                showMessages(s1, s2, s3, panelX, panelY);
                drawHero(frame, heroX, heroY, key);
                frame = 1 - frame;
                playStep();
                delay(22);
            }
            tries++;
        }
    }

    sprintf(s3, "Table full - insertion failed");
    cleardevice();
    setbkcolor(LIGHTCYAN);
    drawTitle(sw);
    drawTable(slots, leftX, topY, boxW, boxH);
    drawPlaced(table, slots, leftX, topY, boxW, boxH);
    showMessages(s1, s2, s3, panelX, panelY);
    shortBeep(520, 160);
    return -1;
}

int main() {
    int gd = DETECT, gm;
    int sw, sh;
    int n, i;
    int slots = SLOTS;

    printf("Welcome to HashHero simulator\n");
    printf("Table fixed to %d slots (0 to %d).\n", slots, slots - 1);
    printf("How many keys do you want to insert? (max %d): ", MAX_KEYS);
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) return 0;
    if (n > MAX_KEYS) n = MAX_KEYS;

    int *keys = (int *)malloc(n * sizeof(int));
    printf("Enter %d keys (space or newline separated):\n", n);
    for (i = 0; i < n; i++) scanf("%d", &keys[i]);

    /* initialize graphics - empty string works for WinBGIm in most setups */
    initgraph(&gd, &gm, "");

    sw = getmaxx(); sh = getmaxy();
    setbkcolor(LIGHTCYAN); cleardevice();

    playWelcome();
    drawTitle(sw);

    int panelX = sw - 420, panelY = 70;
    showInfo(panelX, panelY, slots, n);

    int margin = 60;
    int availW = sw - margin * 2 - 420;
    if (availW < 300) availW = sw - margin * 2;
    int boxW = availW / slots;
    if (boxW > 120) boxW = 120;
    if (boxW < 48) boxW = 48;
    int boxH = boxW * 2 / 3;
    int tableW = boxW * slots;
    int leftX = (sw - 420 - tableW) / 2;
    if (leftX < 30) leftX = 30;
    int topY = sh / 2 - boxH / 2 + 40;

    int *table = (int *)malloc(slots * sizeof(int));
    for (i = 0; i < slots; i++) table[i] = -1;

    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(40, 60, "Using hash function: key % slots");
    drawTable(slots, leftX, topY, boxW, boxH);

    for (i = 0; i < n; i++) {
        animateInsert(table, slots, leftX, topY, boxW, boxH, panelX, panelY, keys[i]);
    }

    showMessages("All done. Press any key to exit.", NULL, NULL, panelX, panelY);
    shortBeep(1200, 80); delay(40); shortBeep(1400, 120);

    getch();
    closegraph();
    free(table); free(keys);
    return 0;
}
