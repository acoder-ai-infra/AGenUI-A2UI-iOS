//
//  AGenUIMessageListener.h
//  https://github.com/acoder-ai-infra/AGenUI
//
//  Created by acoder-ai-infra on 2026/3/18.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// AGenUI message listener protocol
///
/// Implement this protocol to receive AGenUI event notifications from the C++ layer
@protocol AGenUIMessageListener <NSObject>

/// Handle create surface event
///
/// Called when the server requests to create a new UI Surface
///
/// @param surfaceId Unique identifier for the Surface
/// @param catalogId Component catalog identifier
/// @param theme Theme parameters dictionary
/// @param sendDataModel Whether to send back the data model
- (void)onCreateSurfaceWithSurfaceId:(NSString *)surfaceId
                            catalogId:(NSString *)catalogId
                                theme:(NSDictionary<NSString *, NSString *> *)theme
                        sendDataModel:(BOOL)sendDataModel;

/// Handle update components event
///
/// Called when the server requests to update components in a Surface
///
/// @param surfaceId Surface identifier
/// @param components Array of component JSON strings
- (void)onUpdateComponentsWithSurfaceId:(NSString *)surfaceId
                             components:(NSArray<NSString *> *)components;

/// Handle delete surface event
///
/// Called when the server requests to delete a Surface
///
/// @param surfaceId Identifier of the Surface to delete
- (void)onDeleteSurfaceWithSurfaceId:(NSString *)surfaceId;

@end

NS_ASSUME_NONNULL_END
