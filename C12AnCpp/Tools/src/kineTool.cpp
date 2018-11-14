#include "kineTool.h"

void tools::kineTool::execute( core::tuple *tpl, root::particle *p, std::string prefix){

  tpl->column( "PX", p->Px(), prefix );
}

