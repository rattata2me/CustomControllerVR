#ifndef INAME_SRC_INAME_PROGRAM_H_
#define INAME_SRC_INAME_PROGRAM_H_

#include <map>
#include <chrono>
#include <thread>
#include <fstream>

#include "common.h"

#include "json.h"

#include "log.h"
#include "InameComponent.h"

static const std::string DEFAULT_SETTINGS_LOCATION = "settings.iname";
static const int TICKRATE_MAXIMUN = -1;
static const std::string VALUE_NULL = "null_value";

// Nlohmann library seems sweet, why not use it?
using json = nlohmann::json;

class InameProgramConfig{
public:
	
	//A task for someone that uses an ide, refractor, change tickrate to ticktime
	int tickrate = TICKRATE_MAXIMUN;
};

typedef std::map<int, InameComponent*> ComponentsMap;

class InameProgram{

public:
	
	InameProgram(InameProgramConfig* config);
	virtual ~InameProgram();
	InameComponent* getComponent(int id);
	virtual void onStart() = 0;
	virtual void onStop() = 0;
	void clearComponents();
	void addComponent(InameComponent* component_p);
	void start();
	virtual void tick() = 0;
	void stop();
	void readSettings(std::string settings_file_location = DEFAULT_SETTINGS_LOCATION);
	
	json getValueFromSettings(std::string name);
	
private:
	int tickrate;
	bool running;
	void enterMainLoop();
	ComponentsMap components;

protected:
	std::string json_string;
	
};

#endif