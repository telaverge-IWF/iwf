#ifndef __CMAPIINTERFACE_H_
#define __CMAPIINTERFACE_H_

class CMAPIInterface
{
public:
   virtual void HandleDREConfigResponse(DRECfgResp   *resp, void *Cookie) = 0;
};

#endif  // __CMAPIINTERFACE_H_

