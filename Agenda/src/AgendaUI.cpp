#include "AgendaUI.hpp"
#include <iomanip>
using namespace std;
AgendaUI::AgendaUI()
{

}
void AgendaUI::OperationLoop(void)
{
	while(1)
	{
		startAgenda();
		if(executeOperation(getOperation()))
		{

			while(1)
			{
				if(m_userName.size()==0)
				{
					break;
				}
				if(m_agendaService.userLogIn(m_userName,m_userPassword)){
					cout << "---------------------------Agenda--------------------------" << endl;
					cout << "Action:                                                    " << endl;
					cout << "o   - log out Agenda                                       " << endl;
					cout << "dc  - delete Agenda account                                " << endl;
					cout << "lu  - list all Agenda user                                 " << endl;
					cout << "cm  - create a meeting                                     " << endl;
				    cout << "la  - list all meetings                                    " << endl;
					cout << "las - list all sponsor meetings                            " << endl;
					cout << "lap - list all participate meetings                        " << endl;
					cout << "qm  - query meeting by title                               " << endl;
					cout << "qt  - query meeting by time interval                       " << endl;
					cout << "dm  - delete meeting by title                              " << endl;
					cout << "da  - delete all meetings                                  " << endl;
					cout << "-----------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					cout << "Agenda@" << m_userName << " : #";
					string k=getOperation();
					executeOperation(k);	
				}					
			}
		}else{
			break;
		}
	}
}


void AgendaUI::startAgenda(void)
{
	cout << "----------------------Agenda-----------------------" << endl;
	cout << "Action :                                           " << endl;
	cout << "l   - log in Agenda by user name and password      " << endl;
	cout << "r   - register an Agenda account                   " << endl;
	cout << "q   - quit Agenda                                  " << endl;
	cout << "---------------------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << "Agenda : ~$";
}

    /**
     * catch user's operation
     * @return the operation
     */
std::string AgendaUI::getOperation()
{
	string op;
	cin >> op;
	return op;
}

    /**
     * execute the operation
     * @return if the operationloop continue
     */
bool AgendaUI::executeOperation(std::string t_operation)
{
	if(t_operation=="l")
	{
		userLogIn();
		return true;
	}
	if(t_operation=="r")
	{
		userRegister();
		return true;
	}
	if(t_operation=="q")
	{
		return false;
	}
	if(t_operation=="o")
	{
		userLogOut();
		return true;
	}
	if(t_operation=="dc")
	{
		deleteUser();
		return true;
	}	
	if(t_operation=="lu")
	{
		listAllUsers();
		return true;
	}	
	if(t_operation=="cm")
	{
		createMeeting();
		return true;
	}	
	if(t_operation=="la")
	{
		listAllMeetings();
		return true;
	}	
	if(t_operation=="las")
	{
		listAllSponsorMeetings();
		return true;
	}
	if(t_operation=="lap")
	{
		listAllParticipateMeetings();
		return true;
	}
	if(t_operation=="qm")
	{
		queryMeetingByTitle();
		return true;
	}
	if(t_operation=="qt")
	{
		queryMeetingByTimeInterval();
		return true;
	}
	if(t_operation=="dm")
	{
		deleteMeetingByTitle();
		return true;
	}
	if(t_operation=="da")
	{
		deleteAllMeetings();
		return true;
	}
	return false;
}

    /**
     * user Login
     */
void AgendaUI::userLogIn(void)
{
	cout << "[log in] [user name] [password]" << endl;
	cout << "[log in]";
	cin >> m_userName >> m_userPassword;
	if(m_agendaService.userLogIn(m_userName,m_userPassword))
	{
		cout << "[log in] succeed!" << endl;
	}else{
		cout << "[error] log in fail!" << endl;
		m_userName="";
	}

}

    /**
     * user regist
     */
void AgendaUI::userRegister(void)
{
	string name,password,email,phone;
	cout << "[register] [user name] [password] [email] [phone]" << endl;
	cout << "[register]";
	cin >> name >> password >> email >> phone;
	if(m_agendaService.userRegister(name,password,email,phone))
	{
		cout << "[register] succeed!" << endl;
	}else{
		cout << "[register] register fail!" << endl;
	}
}

    /**
     * quit the Agenda
     */
void AgendaUI::quitAgenda(void)
{
}

    /**
     * user logout
     */
void AgendaUI::userLogOut(void)
{
	m_userName="";
}

    /**
     * delete a user from storage
     */
void AgendaUI::deleteUser(void)
{
	if(m_agendaService.deleteUser(m_userName,m_userPassword))
	{
		cout << "[delete agenda account] succeed!" << endl;
		m_userName="";
	}else{
		cout << "[error] fail!" <<endl;
	}
}

    /**
     * list all users from storage
     */
void AgendaUI::listAllUsers(void)
{
	cout << "[list all users]" << endl;
	cout << endl; 
	cout << left <<setw(15) << "name" << setw(20) << "email" << "phone" << endl;
	list<User>::const_iterator it;	
	list<User> u=m_agendaService.listAllUsers();
	for(it=u.begin();it!=u.end();it++)
	{
		cout << left <<setw(15) << (*it).getName() << setw(20) << (*it).getEmail() << (*it).getPhone() << endl;
	}
}

    /**
     * user create a meeting with someone else
     */
void AgendaUI::createMeeting(void)
{
	int p_count;
	string title,starttime,endtime;
	vector<string> v;
	string str;
	cout << "[creat meeting] [the number of participators]" << endl;
	cout << "[creat meeting]";
	cin >> p_count;
	for(int i = 1;i <= p_count;i++)
	{
		cout << "[creat meeting] [please enter the participator " << i << " ]" << endl;
		cout << "[creat meeting]";
		cin >> str;
		v.push_back(str);
	}
	cout << "[creat meeting] [title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[creat meeting]";
	cin >> title >> starttime >> endtime;
	if(m_agendaService.createMeeting(m_userName,title,starttime,endtime,v))
	{
		cout << "[create meeting] succeed!" << endl;
	}else{
		cout << "[create meeting] error!" << endl;
	}
}

    /**
     * list all meetings from storage
     */
void AgendaUI::listAllMeetings(void)
{
	cout << "[list all meetings]" << endl;
	list<Meeting> me=m_agendaService.listAllMeetings(m_userName);
	printMeetings(me);
}

    /**
     * list all meetings that this user sponsored
     */
void AgendaUI::listAllSponsorMeetings(void)
{
	cout << "[list all sponsor meetings]" << endl;
	list<Meeting> me=m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(me);

}

    /**
     * list all meetings that this user take part in
     */
void AgendaUI::listAllParticipateMeetings(void)
{
	cout << "[list all participator meetings]" << endl;
	list<Meeting> me=m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(me);
}

    /**
     * search meetings by title from storage
     */
void AgendaUI::queryMeetingByTitle(void)
{
	string title;
	cout << "[query meeting] [title]:" << endl;
	cout << "[query meeting]";
	cin >> title;
	list<Meeting> me=m_agendaService.meetingQuery(m_userName,title);
	printMeetings(me);
}

    /**
     * search meetings by timeinterval from storage
     */
void AgendaUI::queryMeetingByTimeInterval(void)
{
	string s_time,e_time;
	cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]";
	cout << "[query meetings]";
	cin >> s_time >> e_time;
	cout << "[query meetings]" << endl;
	list<Meeting> me=m_agendaService.meetingQuery(m_userName,s_time,e_time);
	printMeetings(me);
}

    /**
     * delete meetings by title from storage
     */
void AgendaUI::deleteMeetingByTitle(void)
{
	string title;
	cout << "[delete meeting] [title]" << endl;
	cout << "[delete meeting]";
	cin >> title;
	if(m_agendaService.deleteMeeting(m_userName,title))
	{
		cout << "[delete meeting by title] succeed!" << endl;
	}else{
		cout << "[error] delete meeting fail!" << endl;
	}
}

    /**
     * delete all meetings that this user sponsored
     */
void AgendaUI::deleteAllMeetings(void)
{
	if(m_agendaService.deleteAllMeetings(m_userName))
	{
		cout << "[delete all meetings] succeed!" << endl;
	}
}

    /**
     * show the meetings in the screen
     */
void AgendaUI::printMeetings(std::list<Meeting> t_meetings)
{
	cout<<left<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(20)<<"start time"
	<<setw(20)<<"end time"<<"participators"<<endl;
	list<Meeting>::iterator it;
	for(it=t_meetings.begin();it!=t_meetings.end();it++)
	{
		cout<<left<<setw(15)<<(*it).getTitle()<<setw(15)<<(*it).getSponsor()<<setw(20)
		<<Date::dateToString((*it).getStartDate())<<setw(20)<<Date::dateToString((*it).getEndDate());
		vector<string> v=(*it).getParticipator();
		vector<string>::iterator it1=v.begin();
		cout<<*it1; 
		it1++;
		for(;it1!=v.end();it1++)
		{
			cout<<','<<*it1;
		}
		cout << endl;
	}
}
