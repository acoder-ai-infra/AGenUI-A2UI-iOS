//
//  AGenUICXXBridge.h
//  https://github.com/acoder-ai-infra/AGenUI
//
//  Created by acoder-ai-infra on 2026/3/18.
//

#import <Foundation/Foundation.h>

//#define USER_ENV_AMAP

NS_ASSUME_NONNULL_BEGIN

// MARK: - Notification Names

/// Notification sent when a new Surface is created
/// userInfo contains: surfaceId, catalogId, theme, sendDataModel
extern NSString * const AGenUICreateSurfaceNotification;

/// Notification sent when components are updated
/// userInfo contains: surfaceId, components
extern NSString * const AGenUIUpdateComponentsNotification;

/// Notification sent when a Surface is deleted
/// userInfo contains: surfaceId
extern NSString * const AGenUIDeleteSurfaceNotification;

// MARK: - Notification UserInfo Keys

extern NSString * const AGenUISurfaceIdKey;
extern NSString * const AGenUICatalogIdKey;
extern NSString * const AGenUIThemeKey;
extern NSString * const AGenUISendDataModelKey;
extern NSString * const AGenUIComponentsKey;

// MARK: - FunctionCall Callback Type Definitions

/// FunctionCall execution callback
/// @param args JSON string of arguments
/// @return JSON string of execution result
typedef NSString* _Nullable (^AGenUIFunctionCallCallback)(NSString *args);

/// AGenUI C++ Bridge
///
/// Handles interoperability between Swift/ObjC and C++, manages Module lifecycle and event listening
@interface AGenUICXXBridge : NSObject

// MARK: - Singleton

/// Shared singleton instance
+ (instancetype)sharedInstance;

// MARK: - Module Lifecycle Management

/// Initialize C++ Module
- (void)initialize;

/// Start Module
- (void)start;

/// Stop Module
- (void)stop;

/// Shutdown and destroy Module
- (void)shutdown;

// MARK: - Data Transmission

/// Receive text chunk
/// @param data Text chunk string
- (void)receiveTextChunk:(NSString *)data;

/// Receive AGUI event
/// @param data Event data string
- (void)receiveAGUIEvent:(NSString *)data;

/// Send user action to C++ EventDispatcher
/// @param surfaceId Surface ID
/// @param componentId Component ID
/// @param contextJson Context data JSON string
- (void)sendUserAction:(NSString *)surfaceId
           componentId:(NSString *)componentId
               context:(nullable NSString *)contextJson;

/// Sync UI state to data layer
/// @param surfaceId Surface ID
/// @param componentId Component ID
/// @param contextJson Context data JSON string
- (void)syncUIToData:(NSString *)surfaceId
         componentId:(NSString *)componentId
             context:(nullable NSString *)contextJson;

// MARK: - Debug Support

/// Set working directory
/// @param workingDir Working directory path
- (void)setWorkingDirectory:(NSString *)workingDir;

/// Send mock debug message (for simulator debugging only)
/// @param mockData Mock data JSON string
- (void)mockDebugMessage:(NSString *)mockData;

// MARK: - Theme Configuration

/// Load theme configuration
/// @param themeConfigJson Theme configuration JSON string
/// @return Whether loading succeeded
- (BOOL)loadThemeConfig:(NSString *)themeConfigJson;

// MARK: - DesignToken Configuration

/// Load DesignToken configuration
/// @param designTokenConfigJson DesignToken configuration JSON string
/// @return Whether loading succeeded
- (BOOL)loadDesignTokenConfig:(NSString *)designTokenConfigJson;

// MARK: - Theme Mode Management

/// Set day/night mode
/// @param mode Mode configuration, "light" or "dark"
- (void)setDayNightMode:(NSString *)mode;

// MARK: - FunctionCall Management

/// Register FunctionCall
/// @param functionCallName FunctionCall name (e.g. "toast")
/// @param configJson FunctionCall configuration JSON string, containing namespace, name, description, parameters, etc.
/// @param callback FunctionCall execution callback block
/// @return Whether registration succeeded
- (BOOL)registerFunctionCall:(NSString *)functionCallName 
                      config:(NSString *)configJson
                    callback:(AGenUIFunctionCallCallback)callback;

/// Get registered FunctionCall callback (for internal use)
/// @param functionCallName FunctionCall name
/// @return FunctionCall callback, returns nil if not found
- (nullable AGenUIFunctionCallCallback)getFunctionCallCallback:(NSString *)functionCallName;

@end

NS_ASSUME_NONNULL_END
