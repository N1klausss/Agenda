#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
#include <iostream>
using namespace std;

shared_ptr<Storage> Storage::m_instance(nullptr);

  /**
  *   default constructor
  */
Storage::Storage()
{
  readFromFile();
  m_dirty=false;
}

  /**
  *   read file content into memory
  *   @return if success, true will be returned
  */
bool Storage::readFromFile(void)
{
  std::ifstream user_file,meeting_file;
  user_file.open(Path::userPath, ios::in);
  meeting_file.open(Path::meetingPath,ios::in);
  if(!user_file.is_open() || !meeting_file.is_open())
  {
    return false;
  }
  int i,j,k,l,m;
  std::string name,password,email,phone;
  for(std::string str;getline(user_file,str);)
  {
    if(str.size()==0)
    {
      break;
    }
    for(i=0;;i++)
    {
      if(str[i]==',')
      {
        name=str.substr(1,i-2);
        break;
      }
    }
    for(j=i+2;;j++)
    {     
     if(str[j]==',')
      {
        password=str.substr(i+2,j-i-3);
        break;
      }
    }
    for(k=j+2;;k++)
    {
      if(str[k]==',')
      {
        email=str.substr(j+2,k-j-3);
        break;
      }      
    }
    for(l=k+2;;l++)
    {
      if(str[l]=='"')
      {
        phone=str.substr(k+2,l-k-2);
        break;
      }
    }
    User u(name,password,email,phone);
    m_userList.push_back(u);
    str = "";
  }
  std::string sponsor,participator,starttime,endtime,title;
  for(std::string str;getline(meeting_file,str);)
  {
    std::vector<std::string> v;
    Date da1,da2;
    if(str.size()==0)
    {
      break;
    }
    for(i=0;;i++)
    {
      if(str[i]==',')
      {
        sponsor=str.substr(1,i-2);
        break;
      }
    }
    for(j=i+2;;j++)
    {
      if(str[j]==',')
      {
        participator=str.substr(i+2,j-i-2);
        int n,n1=0;
        std::string s;
        for(n=0;n<participator.size();n++)
        {
          if(participator[n]=='&' || participator[n]=='"')
          {
            s=participator.substr(n1,n-n1);
            v.push_back(s);
            n1=n+1;
          }
        }
       break;
      }
    }
    for(k=j+2;;k++)
    {
      if(str[k]==',')
      {
        starttime=str.substr(j+2,k-j-3);
        da1=Date::stringToDate(starttime);
        break;
      }
    }
    for(l=k+2;;l++)
    {
      if(str[l]==',')
      {
        endtime=str.substr(l+2,l-k-3);
        da2=Date::stringToDate(endtime);
        break;
      }
    }
    for(m=l+2;;m++)
    {
      if(str[m]=='"')
      {
        title=str.substr(l+2,m-l-2);
        break;
      }
    }
    Meeting me(sponsor,v,da1,da2,title);
    m_meetingList.push_back(me);
    str = "";
  }
  user_file.close();
  meeting_file.close();
  return true;

}

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
 bool Storage::writeToFile(void)
 {
  std::ofstream u_file,m_file; 
  u_file.open(Path::userPath,ios::out);
  m_file.open(Path::meetingPath,ios::out);
  if(!u_file.is_open() || !m_file.is_open())
  {
    return false;
  }
  list<User>::iterator it1;
  for(it1=m_userList.begin();it1!=m_userList.end();it1++)
  {
    u_file << '"' << (*it1).getName() << '"' << ',';
    u_file << '"' << (*it1).getPassword() << '"' << ',';
    u_file << '"' << (*it1).getEmail() << '"' << ',';
    u_file << '"' << (*it1).getPhone() << '"' << endl;
  }
  list<Meeting>::iterator it2;
  for(it2=m_meetingList.begin();it2!=m_meetingList.end();it2++)
  {
    m_file << '"' << (*it2).getSponsor() << '"' << ',';
    m_file << '"';
    vector<string> v=(*it2).getParticipator();
    vector<string>::iterator it3=v.begin();
    m_file << *it3;
    it3++;
    for(;it3!=v.end();it3++)
    {
      m_file << '&' << *it3;
    }
    m_file << '"' << ',';
    m_file << '"' << Date::dateToString((*it2).getStartDate()) << '"' << ',';
    m_file << '"' << Date::dateToString((*it2).getEndDate()) << '"' << ',';
    m_file << '"' << (*it2).getTitle() << '"' << endl;
  }
  u_file.close();
  m_file.close();
  return true;
 }


  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
 std::shared_ptr<Storage> Storage::getInstance(void)
 {
 	if(Storage::m_instance == nullptr){
    m_instance=std::shared_ptr<Storage> (new Storage());
    return m_instance;
  }
 }

  /**
  *   destructor
  */
  Storage::~Storage()
  {
    sync();
  }


  void Storage::createUser(const User & t_user)
  {
    User u(t_user);
    m_userList.push_back(u);
    m_dirty=true;
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const
  {
    std::list<User> u;
    for(auto &i :m_userList)
    {
      if(filter(i))
      {
        u.push_back(i);
      }
    }
    return u;
  }

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher)
  {
    int up_count=0;
    for(auto &i : m_userList)
    {
      if(filter(i))
      {
        switcher(i);
        up_count++;
        m_dirty=true;
      }
    }
    return up_count;
  }

  /**
  * delete usersAgendaService::
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int Storage::deleteUser(std::function<bool(const User &)> filter)
  {
    int de_count=0;
    list<User>::iterator i;
    for(i=m_userList.begin();i!=m_userList.end();)
    {
      if(filter(*i))
      {
        i=m_userList.erase(i);
        de_count++;
        m_dirty=true;
      }
      else 
      {
        i++;
      }
    }
    return de_count;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void Storage::createMeeting(const Meeting & t_meeting)
  {
    Meeting m(t_meeting);
    m_meetingList.push_back(m);
    m_dirty=true;
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const
  {
    std::list<Meeting> m;
    for(auto &i :m_meetingList)
    {
      if(filter(i))
      {
        m.push_back(i);
      }
    }
    return m;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher)
  {
    int up_count=0;
    for(auto &i : m_meetingList)
    {
      if(filter(i))
      {
        switcher(i);
        up_count++;
        m_dirty=true;
      }
    }
    return up_count;
  }

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter)
  {
    int de_count=0;
    list<Meeting>::iterator i;
    for(i=m_meetingList.begin();i!=m_meetingList.end();)
    {
      if(filter(*i))
      {
        i=m_meetingList.erase(i);
        de_count++;
        m_dirty=true;
      }else{
        i++;
      }
    }
    return de_count;
  }

  /**
  * sync with the file
  */
  bool Storage::sync(void)
  {
    if(m_dirty==false)
    {
      return false;
    }
    else{
      writeToFile();
      m_dirty=false;
      return true;
    }
  }