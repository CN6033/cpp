#include<iostream>
#include<vector>
#include<algorithm>

#include<boost/bind.hpp>
#include<boost/shared_ptr.hpp>

class status
{
public:
  status(const std::string& name):name_(name),ok_(true) {}

  void break_it() {
    ok_=false;
  }

  bool is_broken() const {
    return ok_;
  }

  void report() const {
    std::cout << name_ << " is " <<
      (ok_ ? "working nominally":"terribly broken") << '\n';
  }

private:
  std::string name_;
  bool ok_;
};


int main()
{
    std::vector<status> statuses;
    statuses.push_back(status("status 1"));
    statuses.push_back(status("status 2"));
    statuses.push_back(status("status 3"));
    statuses.push_back(status("status 4"));
    
    statuses[1].break_it();
    statuses[2].break_it();
    
    // This loop does the job correctly, but it's verbose, inefficient 
    // (due to the multiple calls to statuses.end()), and not as clear 
    // as using the algorithm from the Standard Library that exists for 
    // exactly this purpose, for_each. 
    for (std::vector<status>::iterator it=statuses.begin();
           it!=statuses.end();++it) {
      it->report();
    }
    
    std::for_each(
     statuses.begin(),
     statuses.end(),
     std::mem_fun_ref(&status::report));//because the elements are stored by value, 
                                        //what we need is the adaptor mem_fun_ref.
                                        
    std::for_each(
      statuses.begin(),
      statuses.end(),
      boost::bind(&status::report,_1));
    //-------------------------------------------------------------------------
    std::vector<status*> p_statuses;
    p_statuses.push_back(new status("status 1"));
    p_statuses.push_back(new status("status 2"));
    p_statuses.push_back(new status("status 3"));
    p_statuses.push_back(new status("status 4"));
    
    p_statuses[1]->break_it();
    p_statuses[2]->break_it();
    
    std::for_each(
      p_statuses.begin(),
      p_statuses.end(),
      std::mem_fun(&status::report));//we can no longer use mem_fun_ref
    
     std::for_each(
       p_statuses.begin(),
       p_statuses.end(),
       boost::bind(&status::report,_1));
    //------------------------------------------------------------------------
    std::vector<boost::shared_ptr<status> > s_statuses;
    s_statuses.push_back(
      boost::shared_ptr<status>(new status("status 1")));
    s_statuses.push_back(
      boost::shared_ptr<status>(new status("status 2")));
    s_statuses.push_back(
      boost::shared_ptr<status>(new status("status 3")));
    s_statuses.push_back(
      boost::shared_ptr<status>(new status("status 4")));
    s_statuses[1]->break_it();
    s_statuses[2]->break_it();
    
    /*
    mem_fun and mem_fun_ref do not apply, because the smart pointer doesn't 
    have a member function called report, and thus the following code fails to 
    compile.
    std::for_each(
      s_statuses.begin(),
      s_statuses.end(),
      std::mem_fun(&status::report));
    */
    
    std::for_each(
      s_statuses.begin(),
      s_statuses.end(),
      boost::bind(&status::report,_1));
}
