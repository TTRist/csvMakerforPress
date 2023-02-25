// -*- C++ -*-
/*!
 * @file  cvsMakerForPress.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "cvsMakerForPress.h"
#include <fstream>
#include "confReader.hpp"

using namespace std;
string save_path, extension;

enum { MODE, POSITION, LOAD, PORT_LENGTH };
enum {
	NOW_POS,
	ABSOLUTE_POS,
	RELATIVE_POS,
	BASE_RLTPOS,
	BASE_SET,
	BLTOUCH_POS,
	LOAD_POS,
	RELEASE_FORCE,
	NOWPOS_BASE,
	RELOAD_SETTING,
	FULL_AUTO,
	TIME_BLT,
	NOWAIT_BLT
};


// Module specification
// <rtc-template block="module_spec">
static const char* cvsmakerforpress_spec[] =
{
  "implementation_id", "cvsMakerForPress",
  "type_name",         "cvsMakerForPress",
  "description",       "ModuleDescription",
  "version",           "1.0.0",
  "vendor",            "VenderName",
  "category",          "Category",
  "activity_type",     "PERIODIC",
  "kind",              "DataFlowComponent",
  "max_instance",      "1",
  "language",          "C++",
  "lang_type",         "compile",
  ""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
cvsMakerForPress::cvsMakerForPress(RTC::Manager* manager)
// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_posloadIn("posload", m_posload),
	m_makeCSVIn("makeCSV", m_makeCSV)

	// </rtc-template>
{
}

/*!
 * @brief destructor
 */
cvsMakerForPress::~cvsMakerForPress()
{
}



RTC::ReturnCode_t cvsMakerForPress::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("posload", m_posloadIn);
	addInPort("makeCSV", m_makeCSVIn);

	// Set OutPort buffer

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// </rtc-template>

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t cvsMakerForPress::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPress::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPress::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t cvsMakerForPress::onActivated(RTC::UniqueId ec_id)
{
	ifstream infile("./../../../MakedFile/setting.conf");
	if (!infile) {
		cout << "読み込み失敗　パスが違うかも\n";
		return RTC::RTC_ERROR;
	}
	conf::setMap(conf::config_map, infile, R"(=| )");
	infile.close();

	cout << "makeCSVに「end」を入れればファイルが作られません。EXE終了前にやるといいかもね.\n";
	save_path = conf::config_map["SAVE_PATH"];
	extension = conf::config_map["EXTENSION"];
	return RTC::RTC_OK;
}


RTC::ReturnCode_t cvsMakerForPress::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t cvsMakerForPress::onExecute(RTC::UniqueId ec_id)
{
	static ofstream outfile;
	if (m_makeCSVIn.isNew()) {
		outfile.close(); // 何か来たらファイル終了するためのやつ。
		m_makeCSVIn.read();
		string path_and_name = m_makeCSV.data;
		if (path_and_name == "end") 
			outfile.close();
		else
			outfile.open(save_path + path_and_name + extension);
	}

	// recieved posload data
	if (m_posloadIn.isNew()) {
		m_posloadIn.read();

		// output CSV
		if (m_posload.data[MODE] == BASE_SET)
			outfile << "基準点設定[mm]," << m_posload.data[POSITION] << endl;
		else if(m_posload.data[MODE] == BLTOUCH_POS)
			outfile << "BLTouch接触位置[mm]," << m_posload.data[POSITION] << endl;
		else if(m_posload.data[MODE] == LOAD_POS)
			outfile << "圧縮位置[mm]," << m_posload.data[POSITION] << ",圧迫力[g]," << m_posload.data[LOAD] << ",";
		else if(m_posload.data[MODE] == NOWAIT_BLT)
			outfile << "BLTouch接触位置[mm]," << m_posload.data[POSITION] << ",解放後時間[s]," << m_posload.data[LOAD] << endl;

		// output console
		if (m_posload.data[MODE] == BASE_SET)
			std::printf("基準点設定：%.1f[mm]	\n", m_posload.data[POSITION]);
		else if (m_posload.data[MODE] == BLTOUCH_POS)
			std::printf("BLTouch接触位置：%.1f[mm]	\n", m_posload.data[POSITION]);
		else if (m_posload.data[MODE] == LOAD_POS)
			std::printf("圧縮位置：%.1f[mm]	圧迫力：%.1f[g]\n", m_posload.data[POSITION], m_posload.data[LOAD]);
		else if (m_posload.data[MODE] == NOWAIT_BLT)
			std::printf("圧縮位置：%.1f[mm]	時間：%.1f[s]\n", m_posload.data[POSITION], m_posload.data[LOAD]);
	}
	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t cvsMakerForPress::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPress::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPress::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPress::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPress::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

	void cvsMakerForPressInit(RTC::Manager* manager)
	{
		coil::Properties profile(cvsmakerforpress_spec);
		manager->registerFactory(profile,
			RTC::Create<cvsMakerForPress>,
			RTC::Delete<cvsMakerForPress>);
	}

};


