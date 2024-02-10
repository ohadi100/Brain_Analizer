# GDC

The GDC is a component in the PPE platform that proxies the information sent from brain to the Cymotive backend (similar to the MEB Proxy).
In the GDC system, a GDC agent delivers data to a GDC master which eventually passes that data to BE.
In PPE, brain acts as a GDCAgent, by using the OdcAgentGenericLarge & OdcAgentCommonLarge libraries, provided by GDC development team.
PPE brain sends its data (serialized events) in a "fire and forget" manner (does not support ACKs and assumes successful sending on every attempt). 
This lacks the assurance that all chunks were received correctly and retransmitted if needed, but can be mitigated by addition of a feedback mechanism from GDC master's side later 
(as chunks already include their serial chunk number and total number of chunks as described below).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

The project's conanfile must include:
* Updated autogen files for the CommonLarge/GenericLarge interfaces, currently supplied by libtlr
* Updated version of libtlr (currently using libtlr/1.0.6)

For MVP and HCP5, the following are the current entries for libtlr in the conanfile, respectively -

```
self.requires("libtlr/1.0.6@e3swp/stable") // MVP
self.requires("libtlr/1.0.6@e3swp/hcp5_int") // HCP5
```

## Working with GDC

The GDC exposes a regular publisher interface, which is integrated in the BELogic module of the brain.
Unlike proxy the GDC system does not support ACKs at the moment, and assumes successful send on every attempt.

### APIs

The brain interacts with the GDC through the GDCPublisher in BELogic.cpp.
The GDC publisher exposes the following APIs -

```
void SendMsg(someip::message_categories::MessageCategoryType const & category, std::string const & messagePayload);
void SendMsg(someip::message_categories::MessageCategoryType const & category, std::vector<uint8_t> const & messagePayload);
```

Through which brain can send the serialized events to the backend, just like the MEB Proxy.
Example usage -

```
auto publisher = std::make_shared<GDCPublisher>();
publisher->Init();
const std::string payload = "Fantastic bricks and where to grind them";
publisher->SendMsg(payload);
```

### internals

#### Skeleton

Just like other publishers based on PublisherBase, at the root of the API lies an ara skeleton object.
In the GDC system, this object is a derived object that has to implement two interfaces -

```
OdcAgentCommonLargeSkeleton
OdcAgentGenericLargeSkeleton
```

##### OdcAgentGenericLargeSkeleton

The OdcAgentGenericLargeSkeleton interface implements the simple "Send and forget" logic currently implemented in brain.
It is done using the event-type variable called "data" inherited from the interface, through which "data.Send(payload)" is called.

##### OdcAgentCommonLargeSkeleton

The OdcAgentCommonLargeSkeleton interface implements a campaign based effort in which the GDC master delivers brain-specific campaign describing which information should be sent and when.
Currently the OdcAgentCommonLargeSkeleton interface is implemented with stubs. It requires the following functions -

```
::ara::core::Future<getInfoOutput> getInfo() override;
::ara::core::Future<getCampaignsOutput> getCampaigns() override;
::ara::core::Future<getAvailableResourcesOutput> getAvailableResources() override;
::ara::core::Future<estimateCampaignOutput> estimateCampaign(::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const& campaign) override;
::ara::core::Future<addCampaignOutput> addCampaign(::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const& request) override;
::ara::core::Future<removeCampaignOutput> removeCampaign(::ara::stdtypes::String const& uuid) override;
::ara::core::Future<getDataOutput> getData(::ara::stdtypes::String const& resource) override;
::ara::core::Future<setDataOutput> setData(::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const& request) override;
```

#### Chunking

Unlike a regular publisher, the GDC publisher includes a chunking mechanism.
This is implemented in order to bypass certain limitations imposed by the GDC system for buffer length etc.
The chunking mechanism is rather simple and described and implemented in GDCPublisher::SendMsg().

Each chunk consists:
1. Metadata - Information regarding the chunk.
			  That information includes both the total number of chunks that are about to be sent, and the serial number of that chunk out of the total chunks.
2. Payload - Data of the chunk.
			 Currently, as part of the limitations described, the max size of data that each chunk can consist is 1KB (not including the metadata). 
			 In that way, each buffer that is intended to be sent to GDC master, is truncated into several chunks where each one of them is 1KB, and the last chunk is the residue and might be less than 1KB.
			 Namely, there's no padding logic.

As mentioned above, there's no feedback provided from GDC master to ensure getting all chunks and retransmit in case needed.
Though, since each chunk also includes its serial number and the total number of chunks to be sent (inside the metadata part), a feedback mechanism can be easily added from GDC master side.


## Running tests

Currently no tests are available. In the future, there might be a mock for GDC Master.

### Break down into end to end tests

See "Running tests"

## Deployment

* [MVP/HCP5](https://srv-confluence:8443/pages/viewpage.action?pageId=84377802) - The build/deploy information for either platform

## Built With

* [MVP/HCP5](https://srv-confluence:8443/pages/viewpage.action?pageId=84377802) - The build/deploy information for either platform


## License

