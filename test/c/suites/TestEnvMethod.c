/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2010, 2012 Oracle and/or its affiliates.  All rights reserved.
 *
 * $Id$
 */

#include "db.h"
#include "CuTest.h"

int TestSetThreadCount(CuTest *ct) { /* SKIP */

	DB_ENV *dbenv;
	DB *db;

	CuAssert(ct, "db_env_create", db_env_create(&dbenv, 0) == 0);

	dbenv->set_errpfx(dbenv, "TestSetThreadCount");
	CuAssert(ct, "set_thread_count", dbenv->set_thread_count(dbenv, 2) == 0);
	CuAssert(ct, "env->open", dbenv->open(dbenv, ".",
			DB_CREATE | DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_MPOOL |
			DB_INIT_TXN | DB_PRIVATE | DB_THREAD, 0) == 0);

	CuAssert(ct, "db_create", db_create(&db, dbenv, 0) == 0);
	CuAssert(ct, "DB->open", db->open(
	    db, NULL, NULL, "TestSetThreadCount", DB_HASH, DB_CREATE, 0) == 0);

	db->close(db, 0);
	dbenv->close(dbenv, 0);

	return (0);
}
