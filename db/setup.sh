#!/bin/bash
mysql -u root -p < schema.sql #< datainitialization.sql
mysql -u root -p < datainitialization.sql
