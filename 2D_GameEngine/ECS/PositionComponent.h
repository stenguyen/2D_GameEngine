#pragma once
#include "Components.h"

//class constructor that inherits 
//https://www.google.com/search?q=declaring+class+with+colon+cpp&rlz=1C1GCEA_enCA909CA909&sxsrf=ALiCzsYG4OrSMPZ204khtS2MoPYFihxKcQ%3A1657197009580&ei=0dHGYo2EI-OE0PEPr-ugqAM&ved=0ahUKEwjNsND44-b4AhVjAjQIHa81CDUQ4dUDCA4&uact=5&oq=declaring+class+with+colon+cpp&gs_lcp=Cgdnd3Mtd2l6EAMyBwghEAoQoAEyCAghEB4QFhAdMggIIRAeEBYQHTIICCEQHhAWEB06BwgAEEcQsAM6CggAEOQCELADGAE6BggAEB4QFjoKCAAQHhAPEBYQCjoFCAAQgAQ6CAgAEB4QDxAWOgUIIRCgAUoECEEYAEoECEYYAVDLAliLGGC3GWgBcAB4AIABeYgBzw2SAQQxNC41mAEAoAEByAENwAEB2gEGCAEQARgJ&sclient=gws-wiz
class PositionComponent : public Components {
private:
	int xpos;
	int ypos;
public:
	void update() override {
		xpos++;
		ypos++;
	}

	int x() {
		return xpos;
	}

	void x(int x) { xpos = x; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }

};