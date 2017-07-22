#include<stdlib.h>
#include<iostream>

#include<mysql_connection.h>
#include<driver.h>
#include<cppconn/exception.h>
#include<cppconn/prepared_statement.h>
#include<cppconn/statement.h>
#include<cppconn/resultset.h>

using namespace std;
using namespace sql;

int main(void)
{
	try{
		sql::Driver *driver;
		sql::Connection *con;
		sql::PreparedStatement *prep_stmt;
		sql::Statement *stmt;
		sql::ResultSet *res;

		string head,action,type,status,inparams,outparams,errmsg,log;
	    int id,starttime,endtime;

	    string delete_goal;
	    int delete_num;

	    string update_std;
	    int update_std_num;

		cout << "connection to mysql server ...";
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306","root","123456");
		cout << "connected"<<endl;

		con->setSchema("test");

		cout << "Please input the command: myProgram add or myProgram delete or myProgram read or myProgram update" << endl;

		cin >> head >> action;

		if(action == "add"){

			cout << "Please input the add date" <<endl;

			cin >> id >> type >> status >> inparams >> outparams >> starttime >> endtime >> errmsg >> log;
			
			prep_stmt = con->prepareStatement("INSERT INTO destination5(Id,Type,Status,Inparams,Outparams,Starttime,Endtime,Errmsg,Log) VALUES(?,?,?,?,?,?,?,?,?)");

			cout << "add data...";

			prep_stmt->setInt(1,id);
			prep_stmt->setString(2,type);
			prep_stmt->setString(3,status);
			prep_stmt->setString(4,inparams);
			prep_stmt->setString(5,outparams);
			prep_stmt->setInt(6,starttime);
			prep_stmt->setInt(7,endtime);
			prep_stmt->setString(8,errmsg);
			prep_stmt->setString(9,log);

			prep_stmt->execute();

			cout << "done" << endl;

			delete prep_stmt;
		}

		if(action == "delete"){

			cout << "Please input the delete goal and delete data"<<endl;

			cin >> delete_goal >> delete_num;

			prep_stmt = con->prepareStatement("DELETE FROM destination5 WHERE "+delete_goal+"=?");

			cout << "delete data ...";

			prep_stmt->setInt(1,delete_num);
			prep_stmt->execute();

			cout << "done" <<endl;

			delete prep_stmt;

		}

		if(action == "read"){

			stmt = con->createStatement();
			res = stmt->executeQuery("SELECT * FROM destination5");

			cout << "list of data: " <<endl;

			while(res->next()){

				cout << "Id:" << res->getInt(1) << '\t';
				cout << "Type:" << res->getString(2) << '\t';
				cout << "Status:" << res->getString(3) << '\t';
				cout << "Inparams:" << res->getString(4) << '\t';
				cout << "Outparams:" << res->getString(5) << '\t';
				cout << "Starttime:" << res->getInt(6) << '\t';
				cout << "Endtime:" << res->getInt(7) << '\t';
				cout << "Errmsg:" << res->getString(8) << '\t';
				cout << "Log:" << res->getString(9) <<endl;
			}

			delete res;
			delete stmt;
		}

		if(action == "update"){

			cout << "Please input the update standard and update standard data"<<endl;

			cin >> update_std >> update_std_num;

			cout << "Please input the update data with the default order"<<endl;

			cin >> id >> type >> status >> inparams >> outparams >> starttime >> endtime >> errmsg >> log;

			prep_stmt = con->prepareStatement("UPDATE destination5 SET Id=?,Type=?,Status=?,Inparams=?,Outparams=?,Starttime=?,Endtime=?,Errmsg=?,Log=? WHERE "+update_std+"=?");
			
			cout << "updating data ...";

			prep_stmt->setInt(1,id);
			prep_stmt->setString(2,type);
			prep_stmt->setString(3,status);
			prep_stmt->setString(4,inparams);
			prep_stmt->setString(5,outparams);
			prep_stmt->setInt(6,starttime);
			prep_stmt->setInt(7,endtime);
			prep_stmt->setString(8,errmsg);
			prep_stmt->setString(9,log);
			prep_stmt->setInt(10,update_std_num);

			prep_stmt->execute();

			cout << "done" <<endl;

			delete prep_stmt;
		}

		delete con;

	} catch (sql::SQLException &e){
		cout << "# ERR: " <<e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;
	}

	cout << endl;

	return EXIT_SUCCESS;
}