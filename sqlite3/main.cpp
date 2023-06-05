#include <stdio.h>
#include <string>
#include "include/sqlite3.h"

static int Callback(void* data, int argc, char** argv, char** columnName)
{
    printf("%s: \n", (const char*)data);
	for (int i = 0; i < argc; i++)
		printf("%s = %s\n", columnName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

int main()
{
    // sql语句
    // SELECT * FROM COMPANY WHERE ID = 2 AND NAME = 'Allen';
    // SELECT * FROM COMPANY WHERE ID > 2;
    // SELECT ID, ADDRESS FROM COMPANY WHERE NAME LIKE 'Lu%';   // %(任意字符任意个) _（单个字符）
    // SELECT * FROM COMPANY WHERE AGE NOT IN (25, 30);
    // SELECT * FROM COMPANY WHERE SALARY GLOB '2???3';         // 查找长度为 5 位数，且以 2 开头以 3 结尾的任意值
    // SELECT * FROM COMPANY LIMIT 3 OFFSET 2;                  // 获取第 2 个记录后的 3 行
    // SELECT * FROM COMPANY ORDER BY SALARY ASC;               // 将结果按SALARY升序   DESC:降序

    // UPDATE COMPANY SET ADDRESS = 'Houston' WHERE NAME = 'Allen';

    // DELETE FROM COMPANY WHERE NAME = 'Allen';

    const char* createTable;
	createTable = "CREATE TABLE COMPANY("
				  "ID       INT         PRIMARY    KEY   NOT NULL,"
				  "NAME	    TEXT	    NOT NULL,"
				  "AGE	    INT		    NOT NULL,"
				  "ADDRESS  CHAR(50),"
				  "SALARY	REAL);";
    const char* insertData;
	insertData = "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) "
				 "VALUES (1, 'Paul',  32, 'California', 20000.0);"
				 "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) "
				 "VALUES (2, 'Allen', 25, 'Texas',      15000.0);";
    const char* updateData;
	updateData = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; "
				 "SELECT * from COMPANY";
    const char* deleteData;
	deleteData = "DELETE from COMPANY where ID=2; "
				 "SELECT * from COMPANY";

    char* errMsg;
    sqlite3* db;
    int rc;
    rc = sqlite3_open("test.db", &db);

    // 普通读写
    rc = sqlite3_exec(db, createTable, Callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // 开启事务
    rc = sqlite3_exec(db, "begin", 0, 0, 0);
        // ...loop
    rc = sqlite3_exec(db, insertData, Callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    rc = sqlite3_exec(db, "commit", 0, 0, 0);

    // 执行编译
    rc = sqlite3_exec(db, "begin;", 0, 0, 0);
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY)"
                      "VALUES(?, ?, ?, ?, ?)";
    sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, 0);
        // ...loop
    sqlite3_reset(stmt);
    sqlite3_bind_int(stmt, 1, 12345);
    sqlite3_bind_text(stmt, 2, "Luu", -1, NULL);
    sqlite3_bind_int(stmt, 3, 25);
    sqlite3_bind_text(stmt, 4, "China", -1, NULL);
    sqlite3_bind_double(stmt, 5, 100.86);
    sqlite3_step(stmt);
        // ...end loop
    sqlite3_finalize(stmt);
    rc = sqlite3_exec(db, "commit", 0, 0, &errMsg);
    return 0;
}