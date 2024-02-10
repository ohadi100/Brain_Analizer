# CampaignConfiguration

The current Campaign Configuration structure is defined in `CampaignConfiguration.proto`.
It's including a KeyID and a UUID (both are optional).

### addCampaign requests
When an `addCampaign` request is sent, it contains a campaign field, which is this protobuf, containing **only** a KeyID.
Besided a campaign field, it also contains a UUID field:

```
struct AddCampaignRequest
{
   ::ara::stdtypes::String uuid{};
   Signature signature{};
   Campaign campaign{};
}
```
### Campaign Configuration usage
Since both should be persistent, and Protobuf 3.0 defining all fields to be optional,
We created a single `CampaignConfiguration` proto that defines both of those structures:
```
{ // From the addCampaign request.data:
   KeyID: 13579
}
```
And:
```
{ // To be saved in the persistent storage.
   KeyID: 13579,
   UUID: "08e484e6-f638-52ec-ada5-d865b08814ce"
}
```
This way we can use the same CampaignConfiguration to both receive `addCampaign` requests and store the campaign data in the persistent memory.

### Campaign Configuration Creation
The protobuf is compiled using `protoc`, with the following command line:
```
protoc --cpp_out=. CampaignConfiguration.proto
```

This command will output both `CampaignConfiguration.cpp` and `CampaignConfiguration.hpp` to the working directory.

Use different `protoc` versions to control the version of the Protobuf (and the required protobuf library version).