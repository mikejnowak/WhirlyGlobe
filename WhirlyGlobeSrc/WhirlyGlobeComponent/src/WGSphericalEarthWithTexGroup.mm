/*
 *  WGSphericalEarthWithTexGroup.mm
 *  WhirlyGlobeComponent
 *
 *  Created by Steve Gifford on 7/21/12.
 *  Copyright 2011 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import "WGSphericalEarthWithTexGroup_private.h"

using namespace Eigen;
using namespace WhirlyKit;
using namespace WhirlyGlobe;

@implementation WGSphericalEarthWithTexGroup
{
    WhirlyGlobeSphericalEarthLayer *earthLayer;
    WhirlyKitTextureGroup *texGroup;
}

- (id)initWithWithLayerThread:(WhirlyKitLayerThread *)layerThread scene:(WhirlyGlobe::GlobeScene *)globeScene texGroup:(NSString *)texGroupName
{
    self = [super init];
    if (self)
    {
        texGroup = [[WhirlyKitTextureGroup alloc] initWithInfo:texGroupName];
        if (!texGroup)
        {
            self = nil;
            return nil;
        }
        earthLayer = [[WhirlyGlobeSphericalEarthLayer alloc] initWithTexGroup:texGroup];
        [layerThread addLayer:earthLayer];
    }
    
    return self;
}

- (void)cleanupLayers:(WhirlyKitLayerThread *)layerThread scene:(WhirlyGlobe::GlobeScene *)globeScene
{
    [layerThread removeLayer:earthLayer];
    earthLayer = nil;
    texGroup = nil;
}

@end