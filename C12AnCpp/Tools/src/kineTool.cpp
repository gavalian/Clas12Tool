#include "Tools/kineTool.h"

void tools::kineTool::execute( core::tuple *tpl, root::particle *p, std::string prefix){

  tpl->column( "PX", p->Px(), prefix );
  tpl->column( "PY", p->Py(), prefix );
  tpl->column( "PZ", p->Pz(), prefix );
  tpl->column( "E",  p->E(),  prefix );
}

