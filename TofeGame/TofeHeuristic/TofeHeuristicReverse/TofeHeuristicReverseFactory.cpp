//----------------------------------------------------------------------------
#include "TofeHeuristicReverseFactory.h"

string TofeHeuristicReverseFactory::register_key
= SgHeuristicEvaluator<TofeGame, TofeHeuristicFactory>
::registerFactory("HeuristicReverse", new TofeHeuristicReverseFactory());
