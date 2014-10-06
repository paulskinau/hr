#!/bin/bash
mysql -u root -p < test1.sql
mysql -u root -p < test2.sql
php test2.php

