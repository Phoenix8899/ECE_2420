BSTKeyVal<std::string, BSTKeyVal<std::string, int> > outer;
BSTKeyVal<std::string, int> inner;
std::shared_ptr<KeyVal<std::string, int> > pKeyVal(new BSTKeyVal<std::string, int>); 
