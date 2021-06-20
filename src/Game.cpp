#include "Main.h"
#include "Game.h"
int bg_image;
int npc_image;
int npc_x[8];	
int npc_y[8];	
int start[8];
int mouse_x;
int mouse_y;
int speed[8];
int player_image;
int click_count;
int player_x;
int player_y;
int bullet_x;
int bullet_y;


//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph("data/player.bmp");
	npc_image = LoadGraph( "data/npc.bmp" );
	bg_image = LoadGraph( "data/bg.bmp" );
	player_x = 50;
	player_y = 240;
	for (int i = 0; i < 8; ++i) {
		start[i] = GetRand(100);
		npc_x[i] = 690 + start[i];
		npc_y[i] = GetRand(430);
		speed[i] = GetRand(3);
	}
	bullet_x = 1000;
	bullet_y = 1000;
	click_count = 0;
}
//---------------------------------------------------------------------------------
//	XVˆ—
//---------------------------------------------------------------------------------
void GameUpdate()
{
	bullet_x += 25;
	
	if (CheckHitKey(KEY_INPUT_W)) {
		player_y -= 10;
		bullet_y = player_y+25;
		if (player_y < 0) {
			player_y = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		player_y += 10;

		bullet_y = player_y+25;
		if (player_y > 430) {
			player_y = 430;

		}
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		bullet_x = 80;
		bullet_y = player_y + 25;
	}


	for (int i = 0; i < 8; ++i) {
		npc_x[i] -= speed[i]+1;
		mouse_x = GetMouseX();
		mouse_y = GetMouseY();

		if (npc_x[i] <= -50) {
			npc_x[i] = 690;
			npc_y[i] = GetRand(430);
		}
		if (PushMouseInput()) {
			if (mouse_x >= npc_x[i] && mouse_x <= npc_x[i] + 50) {
				if (mouse_y >= npc_y[i] && mouse_y <= npc_y[i] + 50) {
					npc_y[i] = GetRand(430);
					npc_x[i] = 690;
					click_count++;
				}
			}
		}
		if (bullet_x >= npc_x[i] && bullet_x <= npc_x[i] + 50) {
			if (bullet_y >= npc_y[i] && bullet_y <= npc_y[i] + 50) {
				npc_y[i] = GetRand(430);
				npc_x[i] = 690;
				bullet_y = 1000;
				click_count++;
			}
		}

	}
}
//---------------------------------------------------------------------------------
//	•`‰æˆ—
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawGraph(0, 0, bg_image, TRUE);
	DrawGraph(player_x, player_y, player_image, TRUE);
	DrawCircle(bullet_x, bullet_y, 5, GetColor(255, 0, 0));
	for (int i = 0; i < 8; ++i) {
		DrawGraph(npc_x[i], npc_y[i], npc_image, TRUE);
	}

	DrawString( 16, 16, "‚m‚o‚b‰æ–Ê¶‚ÉˆÚ“®i¶‚Ü‚Ås‚Á‚½‚ç‰E‚©‚ço‚Ä‚­‚éj", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "‚m‚o‚bƒNƒŠƒbƒNFÄ‚Ñ‰æ–Ê‰E‚©‚ço‚Ä‚­‚é", GetColor( 255, 255, 0 ) );

	DrawString( 16, 48, "SPACE: ”L‚ÌShot", GetColor( 255, 255, 0 ) );

	DrawFormatString( 16, 64, GetColor( 255, 255, 255 ), "‚m‚o‚bƒNƒŠƒbƒN”F%d", click_count );
}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void GameExit()
{
}
