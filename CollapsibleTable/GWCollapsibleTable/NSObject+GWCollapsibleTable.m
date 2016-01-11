//
//  NSObject+GWCollapsibleTable.m
//  CollapsibleTable
//
//  Created by Greg Wang on 13-1-3.
//  Copyright (c) 2013年 Greg Wang. All rights reserved.
//

#import "NSObject+GWCollapsibleTable.h"
#import "GWCollapsibleTable.h"


@implementation NSObject (GWCollapsibleTable)

#pragma mark - Table View Data Source

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    GWCollapsibleTable *collapsibleTable = (GWCollapsibleTable *)tableView;
	id<GWCollapsibleTableDataSource> dataSource = [collapsibleTable collapsibleTableDataSource];
	if ([dataSource tableView:tableView canCollapseSection:indexPath.section]) {
		if (indexPath.row == 0) {
			return [dataSource tableView:tableView headerCellForCollapsibleSection:indexPath.section];
		}
		return [dataSource tableView:tableView bodyCellForRowAtIndexPath:[NSIndexPath indexPathForRow:(indexPath.row - 1) inSection:indexPath.section]];
	}
	return [dataSource tableView:tableView bodyCellForRowAtIndexPath:indexPath];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    GWCollapsibleTable *collapsibleTable = (GWCollapsibleTable *)tableView;

	id<GWCollapsibleTableDataSource> dataSource = [collapsibleTable collapsibleTableDataSource];
	if ([dataSource tableView:tableView canCollapseSection:section]) {
		if (![collapsibleTable.expandedSections containsIndex:section]) {
			return 1;
		}
		return [dataSource tableView:tableView numberOfBodyRowsInSection:section] + 1;
	}
	return [dataSource tableView:tableView numberOfBodyRowsInSection:section];
}

#pragma mark - Table View Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    GWCollapsibleTable *collapsibleTable = (GWCollapsibleTable *)tableView;

	id<GWCollapsibleTableDataSource> dataSource = [collapsibleTable collapsibleTableDataSource];
	id<GWCollapsibleTableDelegate> delegate = [collapsibleTable collapsibleTableDelegate];
	if ([dataSource tableView:tableView canCollapseSection:indexPath.section]) {
		if (indexPath.row == 0) {
			[collapsibleTable toggleSection:indexPath.section];
		}
		else {
			[delegate tableView:tableView didSelectBodyRowAtIndexPath:[NSIndexPath indexPathForRow:indexPath.row - 1 inSection:indexPath.section]];
		}
	}
	else {
		[delegate tableView:tableView didSelectBodyRowAtIndexPath:indexPath];
	}
}

@end
