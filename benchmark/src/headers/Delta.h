//The Delta class describes a set of gradients that we use for updating the model

#include <unordered_map>

//customized hash function
struct IndexHash {
    std::size_t operator()( const std::vector<int> & index) const {
        std::size_t ret = 0;
	int numDimensions = index.size();
        for (int i = 0; i < numDimensions; i++) {
	    int numBitsToShift = sizeof(std::size_t)/numDimensions * (i+1)+1;
	    ret += std::hash<int>()(index[i]) >> (64-(64/numDimensions)*(i+1));
	}
	return ret;
    }

};

//customized equal function
struct IndexEqual {
    bool operator()(const std::vector<int>& lhs, const std::vector<int>&rhs) const{
       if (lhs.size() != rhs.size()){
           return false;
       } else {
           for (int i = 0; i < lhs.size(); i++) {
	      if (lhs[i] != rhs[i])
		      return false;
	   }
           return true;
       }
    }
};

template<typename Type>
class Delta {

private:
    //the gradients data is stored in a hashmap
    std::unordered_map<std::vector<int>, Type, IndexHash, IndexEqual> * data = nullptr;

public:
    //constructor
    Delta() {
        this->data = new std::unordered_map<std::vector<int>, Type, IndexHash, IndexEqual>();
    }

    //destructor
    ~Delta() {
       delete this->data;
       this->data = nullptr;
    }
    
    //add a new gradient 
    void update(std::vector<int> index, Type newValue) {
       (*data)[index] = newValue;
    }

    //get the gradient data
    std::unordered_map<std::vector<int>, Type, IndexHash, IndexEqual>* getData() {
        return data;
    }
};