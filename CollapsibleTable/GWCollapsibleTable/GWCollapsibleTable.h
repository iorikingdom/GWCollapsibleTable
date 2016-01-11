//
//  GWCollapsibleTable.h
//  CollapsibleTable
//
//  Created by Greg Wang on 13-1-3.
//  Copyright (c) 2013年 Greg Wang. All rights reserved.
//

#import "NSObject+GWCollapsibleTable.h"

@protocol GWCollapsibleTableDataSource <NSObject>

- (BOOL)tableView:(UITableView *)tableView canCollapseSection:(NSInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView headerCellForCollapsibleSection:(NSInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView bodyCellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSInteger)tableView:(UITableView *)tableView numberOfBodyRowsInSection:(NSInteger)section;

// TODO: Support Editing & Reordering Methods

@end

@protocol GWCollapsibleTableDelegate <NSObject>

- (void)tableView:(UITableView *)tableView didSelectBodyRowAtIndexPath:(NSIndexPath *)indexPath;

@optional
- (void)tableView:(UITableView *)tableView willExpandSection:(NSInteger)section;
- (void)tableView:(UITableView *)tableView willCollapseSection:(NSInteger)section;

// TODO: Support Extra Selection Management Methods

// TODO: Support Editing & Reordering Methods

@end


@interface GWCollapsibleTable:UITableView

@property (nonatomic, strong, readonly) NSIndexSet *expandedSections;
@property (nonatomic, strong, readonly) id<GWCollapsibleTableDataSource> collapsibleTableDataSource;
@property (nonatomic, strong, readonly) id<GWCollapsibleTableDelegate> collapsibleTableDelegate;

- (void)toggleSection:(NSInteger)section;

- (UITableViewCell *)headerCellForHeaderSection:(NSInteger)section;
- (UITableViewCell *)bodyCellForBodyRowAtIndexPath:(NSIndexPath *)indexPath;

- (void)selectHeaderSection:(NSInteger)section
                   animated:(BOOL)animated
             scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (void)deselectHeaderSection:(NSInteger)section
                     animated:(BOOL)animated;

- (void)selectBodyRowAtIndexPath:(NSIndexPath *)indexPath
                        animated:(BOOL)animated
                  scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (void)selectBodyRowAtIndexPath:(NSIndexPath *)indexPath
                        animated:(BOOL)animated
                  scrollPosition:(UITableViewScrollPosition)scrollPosition
autoExpandingSectionCallDelegate:(BOOL)callDelegate;
- (void)deselectBodyRowAtIndexPath:(NSIndexPath *)indexPath
                          animated:(BOOL)animated;

- (void)insertHeaderSections:(NSIndexSet *)sections
            withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteHeaderSections:(NSIndexSet *)sections
            withRowAnimation:(UITableViewRowAnimation)animation;

@end
