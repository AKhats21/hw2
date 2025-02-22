#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "user.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */


class MyDataStore : public DataStore {
    public:
        MyDataStore();
        ~MyDataStore();

        /**
         * Adds a product to the data store
         */
        void addProduct(Product* p);

        /**
         * Adds a user to the data store
         */
        void addUser(User* u);

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile);

        void addCart(std::string user, std::vector<Product*> hits, size_t num);
      
        std::vector<Product*> viewCart(std::string user) const;

        void buyCart(std::string user);

        bool usernameSearch(std::string user);





    private:
        std::map<std::string,User*> users_;
        std::vector<Product*> products_;
        std::map<std::string, std::vector<Product*>> carts_;
        std::map<std::string, std::set<Product*>> keywords_;
        //maps keywords to a set of Products

};

#endif
