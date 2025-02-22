#include <string>
#include <set>
#include <vector>
#include "mydatastore.h"
#include "util.h"
#include "product.h"
#include "user.h"



using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    for (Product* &p : products_) {
        delete p;
    }
    for (pair<const string, User*>& u : users_) {
        delete u.second;
    }
}


void MyDataStore::addUser(User* u)
{
    string name = u->getName();
    users_[name] = u;
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    //logic to add to keywords map
    set<string> keyWords = p->keywords();
    for (set<string>::iterator it = keyWords.begin();
    it != keyWords.end(); 
    it++){
        keywords_[*it].insert(p);
    }


    


}

vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    vector<Product*> searchVec;
    set<Product*> searchSet;
    //OR SEARCH
    if (type == 1){
        vector<string>::iterator it = terms.begin();
        while (it != terms.end()) {
            if (it == terms.begin()){
                searchSet = keywords_[*it];
            }
            else {
                searchSet = setUnion(searchSet, keywords_[*it]);
            }
            it++;

        }
        //copying set into return vct
        set<Product*>::iterator its = searchSet.begin();
        while (its != searchSet.end()){
            searchVec.push_back(*its);
            its++;
        }
        
    }
    //AND SEARCH
    else{
        vector<string>::iterator it = terms.begin();
        while (it != terms.end()) {
            if (it == terms.begin()){
                searchSet = keywords_[*it];
            }
            else {
                searchSet = setIntersection(searchSet, keywords_[*it]);
            }
            it++;

        }
        //copying set into return vct
        set<Product*>::iterator its = searchSet.begin();
        while (its != searchSet.end()){
            searchVec.push_back(*its);
            its++;
        }
    }
    return searchVec;
}

void MyDataStore::addCart(string username, vector<Product*> hits, size_t search_num){
    //check for out of bounds search
    if (search_num > hits.size() || search_num < 0){
        cout << "Invalid Request" << endl;
        return;
    }
    //checks if user is valid
    else if (users_.find(username) == users_.end()){
        cout << "Invalid Request" << endl;
        return;
    }

    //1-indexed
    carts_[username].push_back(hits[search_num - 1]);
    cout << "Added to cart for User:" << username << endl;




}

vector<Product*> MyDataStore::viewCart(string u) const {
    // if (users_.find(u) == users_.end()){
    //     cout << "Invalid username" << endl;
    // }
    map<string,vector<Product*>>::const_iterator cartIt = carts_.find(u);
    // if (cartIt == carts_.end()){
    //     cout << "Invalid username" << endl;
    //     return;
    // }

    //iterate thru FIFO vct of 
    const std::vector<Product*>& cart = cartIt->second;
    return cart;
}

void MyDataStore::buyCart(string u){
    if (users_.find(u) == users_.end()){
        cout << "Invalid username" << endl;
        return;
    }
    vector<Product*>::iterator it = carts_[u].begin();
    while (it != carts_[u].end()){
        if ((*it)->getQty() < 1 || (*it)->getPrice() > 
        users_[u]->getBalance()){
            it++;
            continue;
        }
        (*it)->subtractQty(1);
        users_[u]->deductAmount((*it)->getPrice());
        
        //erase increments iterator
        it = carts_[u].erase(it);
    }
}

void MyDataStore::dump(ostream& os){
    os << "<products>" << endl;
    for (vector<Product*>::iterator it = products_.begin(); it != products_.end();
    it++){
        (*it)->dump(os);
    }
    os << "</products>" << endl << "<users>" << endl;
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end();
    it++){
        it->second->dump(os);
    }
    os << "</users>" << endl; 
    
}


bool MyDataStore::usernameSearch(string user){
    if (users_.find(user) == users_.end()){
        return false;
    }
    else {
      return true;
    }
}








