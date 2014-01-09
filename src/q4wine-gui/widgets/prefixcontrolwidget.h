/***************************************************************************
 *   Copyright (C) 2008-2013 by Alexey S. Malakhov <brezerk@gmail.com>     *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

#ifndef PREFIXCONTROLWIDGET_H
#define PREFIXCONTROLWIDGET_H

//System
#include <memory>

//Global config
#include "config.h"

//Database
#include "prefix.h"
#include "dir.h"
#include "icon.h"
#ifndef _OS_DARWIN_
#include "sysmenu.h"
#endif

//Qt includes
#include <QSqlQueryModel>
#include <QTableView>
#include <QCheckBox>
#include <QToolBar>
#include <QMenu>
#include <QHeaderView>
#include <QDate>

#ifdef DEBUG
#include <QDebug>
#endif

//Windows
#include "prefixsettings.h"
#include "process.h"

//q4wine lib
#include "q4wine-lib.h"

class PrefixControlWidget : public QWidget
{
Q_OBJECT
public:
	explicit PrefixControlWidget(QWidget *parent = 0);

signals:

public slots:
	void setDefaultFocus(QString prefixName);
    void updateDtabaseItems();

private:
	//! This is need for libq4wine-core.so import.
	QLibrary libq4wine;
	typedef void *CoreLibPrototype (bool);
	CoreLibPrototype *CoreLibClassPointer;
	std::auto_ptr<corelib> CoreLib;

	void createActions();

	std::auto_ptr<QSqlQueryModel> model;

	std::auto_ptr<QTableView> prefixTable;
	std::auto_ptr<QMenu> menu;
	std::auto_ptr<QAction> prefixAdd;
	std::auto_ptr<QAction> prefixDelete;
	std::auto_ptr<QAction> prefixSettings;
	std::auto_ptr<QAction> prefixImport;
	std::auto_ptr<QAction> prefixExport;
    std::auto_ptr<QAction> prefixSetup;

	void updateTableModel(void);

	// Database classes
	Prefix db_prefix;
	Dir db_dir;
	Icon db_icon;
#ifndef _OS_DARWIN_
    system_menu sys_menu;
#endif

private slots:
	void customContextMenuRequested(const QPoint &pos);
	void itemClicked(const QModelIndex &);

	void prefixAdd_Click(void);
	void prefixDelete_Click(void);
	void prefixExport_Click(void);
	void prefixImport_Click(void);
	void prefixSettings_Click(void);
    void prefixSetup_Click(void);

signals:
	void updateDatabaseConnections();
	void prefixIndexChanged(QString);
    void setTabIndex (int);
};

#endif // PREFIXCONTROLWIDGET_H
