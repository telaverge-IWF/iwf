-- Copyright (c) 2007, 2010, Oracle and/or its affiliates. All rights reserved.
-- 
-- This program is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation; version 2 of the License.
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
-- 
-- You should have received a copy of the GNU General Public License
-- along with this program; if not, write to the Free Software
-- Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

--
-- The inital data for system tables of MySQL Server
--

-- When setting up a "cross bootstrap" database (e.g., creating data on a Unix
-- host which will later be included in a Windows zip file), any lines
-- containing "@current_hostname" are filtered out by mysql_install_db.
set @current_hostname= @@hostname;


-- Fill "db" table with default grants for anyone to
-- access database 'test' and 'test_%' if "db" table didn't exist
CREATE TEMPORARY TABLE tmp_db LIKE db;
INSERT INTO tmp_db VALUES ('%','test','','Y','Y','Y','Y','Y','Y','N','Y','Y','Y','Y','Y','Y','Y','Y','N','N','Y','Y');
INSERT INTO tmp_db VALUES ('%','test\_%','','Y','Y','Y','Y','Y','Y','N','Y','Y','Y','Y','Y','Y','Y','Y','N','N','Y','Y');
INSERT INTO db SELECT * FROM tmp_db WHERE @had_db_table=0;
DROP TABLE tmp_db;


-- Fill "users" table with default users allowing root access
-- from local machine if "users" table didn't exist before
CREATE TEMPORARY TABLE tmp_user LIKE user;
set @current_hostname= @@hostname;
INSERT INTO tmp_user VALUES ('localhost','root','','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','','','','',0,0,0,0,'','');
REPLACE INTO tmp_user SELECT @current_hostname,'root','','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','','','','',0,0,0,0,'','' FROM dual WHERE LOWER( @current_hostname) != 'localhost';
REPLACE INTO tmp_user VALUES ('127.0.0.1','root','','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','','','','',0,0,0,0,'','');
REPLACE INTO tmp_user VALUES ('::1','root','','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','','','','',0,0,0,0,'','');
INSERT INTO tmp_user (host,user) VALUES ('localhost','');
INSERT INTO tmp_user (host,user) SELECT @current_hostname,'' FROM dual WHERE LOWER(@current_hostname ) != 'localhost';
INSERT INTO user SELECT * FROM tmp_user WHERE @had_user_table=0;
DROP TABLE tmp_user;

CREATE TEMPORARY TABLE tmp_proxies_priv LIKE proxies_priv;
INSERT INTO tmp_proxies_priv VALUES ('localhost', 'root', '', '', TRUE, '', now());
REPLACE INTO tmp_proxies_priv SELECT @current_hostname, 'root', '', '', TRUE, '', now() FROM DUAL WHERE LOWER (@current_hostname) != 'localhost';
INSERT INTO  proxies_priv SELECT * FROM tmp_proxies_priv WHERE @had_proxies_priv_table=0;
DROP TABLE tmp_proxies_priv;
