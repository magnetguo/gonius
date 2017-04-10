//----------------------------------------------------------------------------
#include "TofeHeuristicEmptyFactory.h"

string TofeHeuristicEmptyFactory::register_key
= SgHeuristicEvaluator<TofeGame, TofeHeuristicFactory>
::registerFactory("HeuristicEmpty", new TofeHeuristicEmptyFactory());