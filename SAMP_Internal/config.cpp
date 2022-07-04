#include "config.h"

void CONFIG::init() {
	DWORD attribs = GetFileAttributes("configs");
	if (attribs == INVALID_FILE_ATTRIBUTES || !(attribs & FILE_ATTRIBUTE_DIRECTORY)) {
		CreateDirectory("configs", NULL);
	}
}

void CONFIG::save(std::string filename) {
	std::stringstream s;
	s << "configs\\" << filename;
	std::ofstream fw(s.str(), std::ios::out);
	json j;
	j["aimbot"]["enabled"] = G::config.aimbot.enabled;
	j["aimbot"]["aimKey"] = G::config.aimbot.aimKey;
	j["aimbot"]["dontShootMates"] = G::config.aimbot.dontShootMates;
	j["aimbot"]["heightChange"] = G::config.aimbot.heightChange;
	j["aimbot"]["fov"] = G::config.aimbot.fov;
	j["aimbot"]["prediction"] = G::config.aimbot.prediction;
	j["aimbot"]["predictionLvl"] = G::config.aimbot.predictionLvl;
	j["aimbot"]["smoothAim"] = G::config.aimbot.smoothAim;
	j["aimbot"]["smoothSpeed"] = G::config.aimbot.smoothSpeed;

	j["esp"]["ESPBox"] = G::config.esp.ESPBox;
	j["esp"]["ESPBoxColor"] = G::config.esp.ESPBoxColor;
	j["esp"]["mateBox"] = G::config.esp.mateBox;
	j["esp"]["mateBoxColor"] = G::config.esp.mateBoxColor;
	j["esp"]["snapLines"] = G::config.esp.snapLines;
	j["esp"]["snapLinesColor"] = G::config.esp.snapLinesColor;
	j["esp"]["healthESP"] = G::config.esp.healthESP;
	j["esp"]["healthESPColor"] = G::config.esp.healthESPColor;
	j["esp"]["armorESP"] = G::config.esp.armorESP;
	j["esp"]["armorESPColor"] = G::config.esp.armorESPColor;
	j["esp"]["nameESP"] = G::config.esp.nameESP;
	j["esp"]["nameESPColor"] = G::config.esp.nameESPColor;
	j["esp"]["weaponESP"] = G::config.esp.weaponESP;
	j["esp"]["weaponESPColor"] = G::config.esp.weaponESPColor;
	j["misc"]["freecam"] = G::config.misc.freecam;
	j["misc"]["freecamSpeed"] = G::config.misc.freecamSpeed;
	j["misc"]["autoOffRadio"] = G::config.misc.autoOffRadio;
	j["misc"]["holdHorn"] = G::config.misc.holdHorn;

	fw << j.dump(4);
	fw.close();
}

void CONFIG::load(std::string filename) {
	std::stringstream s;
	s << "configs\\" << filename;
	std::ifstream fr(s.str(), std::ios::in);
	json j;
	j = json::parse(fr);
	fr.close();

	G::config.aimbot.enabled = j["aimbot"]["enabled"];
	G::config.aimbot.aimKey = j["aimbot"]["aimKey"];
	G::config.aimbot.dontShootMates = j["aimbot"]["dontShootMates"];
	G::config.aimbot.heightChange = j["aimbot"]["heightChange"];
	G::config.aimbot.fov = j["aimbot"]["fov"];
	G::config.aimbot.prediction = j["aimbot"]["prediction"];
	G::config.aimbot.predictionLvl = j["aimbot"]["predictionLvl"];
	G::config.aimbot.smoothAim = j["aimbot"]["smoothAim"];
	G::config.aimbot.smoothSpeed = j["aimbot"]["smoothSpeed"];

	G::config.esp.ESPBox = j["esp"]["ESPBox"];
	G::config.esp.ESPBoxColor[0] = j["esp"]["ESPBoxColor"][0];
	G::config.esp.ESPBoxColor[1] = j["esp"]["ESPBoxColor"][1];
	G::config.esp.ESPBoxColor[2] = j["esp"]["ESPBoxColor"][2];
	G::config.esp.ESPBoxColor[3] = j["esp"]["ESPBoxColor"][3];

	G::config.esp.mateBox = j["esp"]["mateBox"];
	G::config.esp.mateBoxColor[0] = j["esp"]["mateBoxColor"][0];
	G::config.esp.mateBoxColor[1] = j["esp"]["mateBoxColor"][1];
	G::config.esp.mateBoxColor[2] = j["esp"]["mateBoxColor"][2];
	G::config.esp.mateBoxColor[3] = j["esp"]["mateBoxColor"][3];

	G::config.esp.snapLines = j["esp"]["snapLines"];
	G::config.esp.snapLinesColor[0] = j["esp"]["snapLinesColor"][0];
	G::config.esp.snapLinesColor[1] = j["esp"]["snapLinesColor"][1];
	G::config.esp.snapLinesColor[2] = j["esp"]["snapLinesColor"][2];
	G::config.esp.snapLinesColor[3] = j["esp"]["snapLinesColor"][3];

	G::config.esp.healthESP = j["esp"]["healthESP"];
	G::config.esp.healthESPColor[0] = j["esp"]["healthESPColor"][0];
	G::config.esp.healthESPColor[1] = j["esp"]["healthESPColor"][1];
	G::config.esp.healthESPColor[2] = j["esp"]["healthESPColor"][2];
	G::config.esp.healthESPColor[3] = j["esp"]["healthESPColor"][3];

	G::config.esp.armorESP = j["esp"]["armorESP"];
	G::config.esp.armorESPColor[0] = j["esp"]["armorESPColor"][0];
	G::config.esp.armorESPColor[1] = j["esp"]["armorESPColor"][1];
	G::config.esp.armorESPColor[2] = j["esp"]["armorESPColor"][2];
	G::config.esp.armorESPColor[3] = j["esp"]["armorESPColor"][3];

	G::config.esp.nameESP = j["esp"]["nameESP"];
	G::config.esp.nameESPColor[0] = j["esp"]["nameESPColor"][0];
	G::config.esp.nameESPColor[1] = j["esp"]["nameESPColor"][1];
	G::config.esp.nameESPColor[2] = j["esp"]["nameESPColor"][2];
	G::config.esp.nameESPColor[3] = j["esp"]["nameESPColor"][3];

	G::config.esp.weaponESP = j["esp"]["weaponESP"];
	G::config.esp.weaponESPColor[0] = j["esp"]["weaponESPColor"][0];
	G::config.esp.weaponESPColor[1] = j["esp"]["weaponESPColor"][1];
	G::config.esp.weaponESPColor[2] = j["esp"]["weaponESPColor"][2];
	G::config.esp.weaponESPColor[3] = j["esp"]["weaponESPColor"][3];

	G::config.esp.calcColors.ESPBoxColor = FLOATARR_2_D3DCOLOR(G::config.esp.ESPBoxColor);
	G::config.esp.calcColors.snapLinesColor = FLOATARR_2_D3DCOLOR(G::config.esp.snapLinesColor);
	G::config.esp.calcColors.healthESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.healthESPColor);
	G::config.esp.calcColors.armorESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.armorESPColor);
	G::config.esp.calcColors.nameESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.nameESPColor);
	G::config.esp.calcColors.weaponESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.weaponESPColor);

	G::config.misc.freecam = j["misc"]["freecam"];
	G::config.misc.freecamSpeed = j["misc"]["freecamSpeed"];
	G::config.misc.autoOffRadio = j["misc"]["autoOffRadio"];
	G::config.misc.holdHorn = j["misc"]["holdHorn"];
}

void CONFIG::remove(std::string filename) {
	std::stringstream s;
	s << "configs\\" << filename;
	DeleteFile(s.str().c_str());
}

std::vector<std::string> CONFIG::list() {
	std::vector<std::string> list;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char dir[] = "configs\\*";
	WIN32_FIND_DATA ffd;

	hFind = FindFirstFile(dir, &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		return list;
	}

	do {
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			list.push_back(std::string(ffd.cFileName));
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
	return list;
}