RBTKeyVal<std::string, RBTKeyVal<std::string, int> > outer;
RBTKeyVal<std::string, int> inner;
std::shared_ptr<KeyVal<std::string, int> > pKeyVal(new RBTKeyVal<std::string, int>); 
RBTKeyVal<int, std::string> numeric;
