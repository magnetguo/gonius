//----------------------------------------------------------------------------
#include "TofeHeuristicDiffFactory.h"

string TofeHeuristicDiffFactory::register_key
= SgHeuristicEvaluator<TofeGame, TofeHeuristicFactory>
::registerFactory("HeuristicDiff", new TofeHeuristicDiffFactory());