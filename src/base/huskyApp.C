#include "huskyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
huskyApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

huskyApp::huskyApp(InputParameters parameters) : MooseApp(parameters)
{
  huskyApp::registerAll(_factory, _action_factory, _syntax);
}

huskyApp::~huskyApp() {}

void 
huskyApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<huskyApp>(f, af, s);
  Registry::registerObjectsTo(f, {"huskyApp"});
  Registry::registerActionsTo(af, {"huskyApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
huskyApp::registerApps()
{
  registerApp(huskyApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
huskyApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  huskyApp::registerAll(f, af, s);
}
extern "C" void
huskyApp__registerApps()
{
  huskyApp::registerApps();
}
