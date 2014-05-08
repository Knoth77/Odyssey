#include "stdafx.h"
#include "OdysseyTextGenerator.h"

#include "stdafx.h"
#include "Odyssey.h"
#include "OdysseyTextGenerator.h"
#include "../SimpleSideScrollerFramework/src/sssf/game/Game.h"
#include "../SimpleSideScrollerFramework/src/sssf/graphics/GameGraphics.h"
#include "../SimpleSideScrollerFramework/src/sssf/text/GameText.h"
#include "../SimpleSideScrollerFramework/src/sssf/timer/GameTimer.h"
#include "../SimpleSideScrollerFramework/src/sssf/platforms/Windows/WindowsInput.h"
#include "../SimpleSideScrollerFramework/src/sssf/platforms/Windows/WindowsTimer.h"


wstring	W_SPALSH_TEXT = L"[Press ENTER To Play]";
wstring	W_CONT_TEXT = L"[Press ENTER To Continue]";
wstring	W_MAIN_TEXT_1 = L"Continue Game";
wstring	W_MAIN_TEXT_2 = L"New Game";
wstring	W_MAIN_TEXT_3 = L"Controls";
wstring	W_MAIN_TEXT_4 = L"Quit";

wstring W_PAUSE_TEXT_1 = L"Resume";
wstring W_PAUSE_TEXT_2 = L"Quit";
wstring W_MOUSE_COORDS_TEXT = L"Mouse: (";

OdysseyTextGenerator::OdysseyTextGenerator()
{
	_extraData = L"";
}


OdysseyTextGenerator::~OdysseyTextGenerator()
{
}

void OdysseyTextGenerator::initText(Game *game)
{
	GameText *text = game->getText();
	text->addText(&W_SPALSH_TEXT, 500, 550, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_MAIN_TEXT_1, 500, 550, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_MAIN_TEXT_2, 500, 570, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_MAIN_TEXT_3, 500, 590, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_MAIN_TEXT_4, 500, 610, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerate, 10, 10, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_PAUSE_TEXT_1, 500, 610, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_PAUSE_TEXT_2, 500, 640, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&W_CONT_TEXT, 500, 550, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());

}

void OdysseyTextGenerator::updateText(Game *game)
{
	textToGenerate.clear();
	if (B_DEBUG)
	{
		appendMouseCoords(game);
		appendExtraData(game);
	}
}

void OdysseyTextGenerator::appendMouseCoords(Game *game)
{
	wstringstream wss;
	WindowsInput *input = (WindowsInput*)game->getInput();
	textToGenerate.append(W_MOUSE_COORDS_TEXT);
	wss << input->getMousePoint()->x;
	wss << L", ";
	wss << input->getMousePoint()->y;
	wss << L") ";
	wss << _extraData;
	wss << L"\n";

	textToGenerate.append(wss.str());
}

void OdysseyTextGenerator::appendExtraData(Game* game)
{
	if (game->getGSM()->isGameInProgress())
	{
		int health = game->getGSM()->getSpriteManager()->getPlayer()->getPlayerHealth();
		wstringstream wss;
		textToGenerate.append(L"    ");
		wss << health;
		textToGenerate.append(wss.str());
	}
	//wss << _extraData;
	//WindowsInput *input = (WindowsInput*)game->getInput();
	//textToGenerate.append(wss.str());
	//textToGenerate.append(W_MOUSE_COORDS_TEXT);
}