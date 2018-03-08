#include "AgendaService.hpp"

using namespace std;
AgendaService::AgendaService()
{
	m_storage = Storage::getInstance();
}
AgendaService::~AgendaService()
{
}
bool AgendaService::userLogIn(const std::string userName, const std::string password)
{
	list<User> u;
	u = m_storage->queryUser([userName,password](const User& u1) -> bool{
		if(userName==u1.getName())
		{
			if(password==u1.getPassword()){
				return true;
			}
		}
		return false;
	});
	if(u.size()==0) return false;
	return true;
}
bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone)
{
	list<User> u;
	u = m_storage->queryUser([userName](const User& u1) -> bool{
		if(userName==u1.getName())
		{
			return true;
		}
		return false;
	});
	if(u.size()==0){
	    User u(userName,password,email,phone);
	    m_storage -> createUser(u);
	    return true;
    }
    return false;
}
bool AgendaService::deleteUser(const std::string userName, const std::string password)
{
	 int count=m_storage->deleteUser([userName , password](const User& u) -> bool{
	 	if(userName==u.getName() && password==u.getPassword()){
	 		return true;
	 	}else{
	 		return false;
	 	}
	 });
	 if(count==0){
	 	return false;
	 }else{
	    int count1=m_storage ->deleteMeeting([userName](const Meeting& me) ->bool{
	    	if(userName==me.getSponsor()){
	    		return true;
	    	}
	    	vector<string>::iterator it;
	    	vector<string> v=me.getParticipator();
	    	for(it=v.begin();it!=v.end();it++)
	    	{
	    		if(userName==*it){
	    			return true;
	    		}
	    	}
	    	return false;
	    });
	    return true;
	 }
}
std::list<User> AgendaService::listAllUsers(void) const
{
	list<User> u;
	u=m_storage->queryUser([](const User& u1)->bool{return true;});
	return u;
}
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator)
{
	Date d1=Date::stringToDate(startDate);
	Date d2=Date::stringToDate(endDate);
	Meeting me(userName,participator,d1,d2,title);
	list<Meeting> me2;
	me2=m_storage->queryMeeting([userName,title,participator,startDate,endDate](const Meeting& me1) -> bool{
		if(title==me1.getTitle())
		{
			return true;
		}else{
			if(userName==me1.getSponsor())
			{
				if(Date::stringToDate(startDate) >= me1.getEndDate() || Date::stringToDate(endDate) <= me1.getStartDate()){
					return false;
				}
			}else{
				vector<string>::const_iterator it;
				for(it=participator.begin();it!=participator.end();it++)
				{
					if(*it==userName){
						return true;
					}
				}
			}
		}
	});
	if(me2.size()==0)
	{
		m_storage->createMeeting(me);
		return true;
	}
	return false;

}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const
{
	list<Meeting> m;
	m = m_storage->queryMeeting([userName,title](const Meeting& me) -> bool{
	    if(title==me.getTitle()){
	    	if(userName==me.getSponsor()){
	    	return true;
	        }
	        vector<string>::const_iterator it;
	        vector<string> v=me.getParticipator();
	        for(it=v.begin();it!=v.end();it++)
	        {
	    	    if(userName==*it){
	    		    return true;
	    	    }
	        }
	    }
	    return false;
	});
	return m;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const
{
	list<Meeting> m;
	m = m_storage->queryMeeting([userName,startDate,endDate](const Meeting& me) -> bool{
	    if(Date::stringToDate(startDate)>=me.getStartDate() && Date::stringToDate(endDate) <=me.getEndDate())	
	    {
	    	if(userName==me.getSponsor()){
	    	    return true;
	        }
	        vector<string>::const_iterator it;
	        vector<string> v=me.getParticipator();
	        for(it=v.begin();it!=v.end();it++)
	        {
	    	    if(userName==*it){
	    		    return true;
	    	    }
	        }
	    }
	    return false;
	});
	return m;	
}
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const
{
	list<Meeting> m;
	m = m_storage->queryMeeting([userName](const Meeting& me) -> bool{
	    if(userName==me.getSponsor()){
	    	return true;
	    }
	    vector<string>::const_iterator it;
	    vector<string> v=me.getParticipator();
	    for(it=v.begin();it!=v.end();it++)
	    {
	    	if(userName==*it){
	    		return true;
	    	}
	    }
	    return false;
	});
	return m;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const
{
	list<Meeting> m;
	m = m_storage->queryMeeting([userName](const Meeting& me) -> bool{
	    if(userName==me.getSponsor()){
	    	return true;
	    }
	    return false;
	});
	return m;	
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const
{
	list<Meeting> m;
	m = m_storage->queryMeeting([userName](const Meeting& me) -> bool{
	    vector<string>::const_iterator it;
	    vector<string> v=me.getParticipator();
	    for(it=v.begin();it!=v.end();it++)
	    {
	    	if(userName==*it){
	    		return true;
	    	}
	    }
	    return false;
	});
	return m;	
}
bool AgendaService::deleteMeeting(const std::string userName, const std::string title)
{
	int count=m_storage->deleteMeeting([userName,title](const Meeting& me) ->bool{

	    if(title==me.getTitle()){
	    	if(userName==me.getSponsor()){
	    	    return true;
	        }
	        vector<string>::const_iterator it;
	        vector<string> v=me.getParticipator();
	        for(it=v.begin();it!=v.end();it++)
	        {
	    	    if(userName==*it){
	    		    return true;
	    	    }
	        }
	    }
	    return false;
    });
    if(count==0) return false;
    return true;
}
bool AgendaService::deleteAllMeetings(const std::string userName)
{
	int count=m_storage->deleteMeeting([userName](const Meeting& me) ->bool{
	    if(userName==me.getSponsor()){
	    	return true;
	    }
	    return false;
    });
    if(count==0) return false;
    return true;	
}
void AgendaService::startAgenda(void)
{
	AgendaService();
}
void AgendaService::quitAgenda(void)
{
	m_storage->~Storage();
}