// -*- C++ -*-
/*!
 * @file  cvsMakerForPressTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "cvsMakerForPressTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* cvsmakerforpress_spec[] =
  {
    "implementation_id", "cvsMakerForPressTest",
    "type_name",         "cvsMakerForPressTest",
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
cvsMakerForPressTest::cvsMakerForPressTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_posloadIn("posload", m_posload)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
cvsMakerForPressTest::~cvsMakerForPressTest()
{
}



RTC::ReturnCode_t cvsMakerForPressTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers

  // Set OutPort buffer
  addOutPort("posload", m_posloadOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t cvsMakerForPressTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPressTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPressTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t cvsMakerForPressTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t cvsMakerForPressTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t cvsMakerForPressTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t cvsMakerForPressTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPressTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPressTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPressTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvsMakerForPressTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void cvsMakerForPressTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(cvsmakerforpress_spec);
    manager->registerFactory(profile,
                             RTC::Create<cvsMakerForPressTest>,
                             RTC::Delete<cvsMakerForPressTest>);
  }

};


