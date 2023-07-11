
List of all commands available for TCAP MN interpreter and all TCAP related
command descriptions (from help of interactive interpreter shell).

/==========================================\
| Multi-Nodes Test Tool (MNT)              |
|                                          |
| (C) 2001 IntelliNet Technologies.        |
\==========================================/


Type '?<CR>' for help.


>>> ?all

List of all available commands:
===============================

Breakpoint
Exit
InitializeGcs
InitializeNodes
InitializeNodesSyncPoints
Print
PrintFile
PublishNodeSyncPointReached
RedirectStdout
SetInternalDebugOff
SetInternalDebugOn
SetInternalParserDebugOff
SetInternalParserDebugOn
Sleep
System
TcapAllocateDialogueId
TcapAssembleBeginDialogue
TcapAssembleEndDialogue
TcapAssembleInvokeComponent
TcapAssembleResultLastComponent
TcapByteArrayToInvokeId
TcapByteArrayToLinkedId
TcapByteArrayToOperation
TcapByteArrayToPointCode
TcapByteArrayToQualityOfService
TcapByteArrayToSccpAddress
TcapDisassembleBeginDialogue
TcapDisassembleEndDialogue
TcapDisassembleInvokeComponent
TcapDisassembleResultLastComponent
TcapGetComponentType
TcapGetDialogueType
TcapGetNextEvent
TcapInitialize
TcapInvokeIdToByteArray
TcapIsComponentEvent
TcapIsDialogueEvent
TcapLinkedIdToByteArray
TcapOperationToByteArray
TcapPeekNextEvent
TcapPointCodeToByteArray
TcapPrintAddress
TcapPrintComponent
TcapPrintDialogue
TcapQualityOfServiceToByteArray
TcapReceiveComponent
TcapReceiveDialogue
TcapSccpAddressToByteArray
TcapSendComponent
TcapSendDialogue
TcapTerminate
TerminateGcs
TerminateNodes
TerminateNodesSyncPoints
WaitForNodeJoinPoint
WaitForNodeSyncPoint

-------------------------------------------------------------------------------

>>> ?TcapAllocateDialogueId

Allocate a Dialogue Id.

<integer> TcapAllocateDialogueId(<integer>):

 -> Argument #0 (type integer):
        Dialogue Id (out).

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapAssembleBeginDialogue

Assemble a Begin Dialogue (into a byte array). Only the
parameters relevant to a request can be specified.

<byte array> TcapAssembleBeginDialogue(
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>):

 -> Argument #0 (type byte array):
        Quality of Service.

 -> Argument #1 (type byte array):
        Application Context Name.

 -> Argument #2 (type byte array):
        User Information.

 -> Argument #3 (type byte array):
        Origination Address.

 -> Argument #4 (type byte array):
        Destination Address.

 -> Argument #5 (type byte array):
        Origination Point Code.

 -> Argument #6 (type byte array):
        Destination Point Code.

 -> Return value (type byte array):
        Assembled Begin Dialogue.

-------------------------------------------------------------------------------

>>> ?TcapAssembleEndDialogue

Assemble an End Dialogue (into a byte array). Only the
parameters relevant to a request can be specified.

<byte array> TcapAssembleEndDialogue(
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <boolean>):

 -> Argument #0 (type byte array):
        Quality of Service.

 -> Argument #1 (type byte array):
        Application Context Name.

 -> Argument #2 (type byte array):
        User Information.

 -> Argument #3 (type boolean):
        Termination.


 -> Return value (type byte array):
        Assembled End Dialogue.

-------------------------------------------------------------------------------

>>> ?TcapAssembleInvokeComponent

Assemble an Invoke Component (into a byte array). Only the
parameters relevant to a request can be specified.

<byte array> TcapAssembleInvokeComponent(
                            <integer>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <integer>):

 -> Argument #0 (type integer):
        Operation Class (1, 2, 3 or 4).

 -> Argument #1 (type byte array):
        Invoke Id.

 -> Argument #2 (type byte array):
        Linked Id.

 -> Argument #3 (type byte array):
        Operation.

 -> Argument #4 (type byte array):
        Parameters.

 -> Argument #5 (integer):
        Timeout.

 -> Return value (type byte array):
        Assembled Invoke Component.

-------------------------------------------------------------------------------

>>> ?TcapAssembleResultLastComponent

Assemble a Result Last Component (into a byte array). Only
the parameters relevant to a request can be specified.

<byte array> TcapAssembleResultLastComponent(
                            <byte array>,
                            <byte array>,
                            <byte array>):

 -> Argument #0 (type byte array):
        Invoke Id.

 -> Argument #1 (type byte array):
        Operation.

 -> Argument #2 (type byte array):
        Parameters.

 -> Return value (type byte array):
        Assembled Result Last Component.

-------------------------------------------------------------------------------

>>> ?TcapByteArrayToInvokeId

Convert a byte array to an Invoke Id (as integer).

<integer> TcapByteArrayToInvokeId(<byte array>):

 -> Argument #0 (type byte array):
        Byte array representing an Invoke Id from suitable
        commands.

 -> Return value (type integer):
        Invoke Id.

-------------------------------------------------------------------------------

>>> ?TcapByteArrayToLinkedId

Convert a byte array to a Linked Id (as integer).

<integer> TcapByteArrayToLinkedId(<byte array>):

 -> Argument #0 (type byte array):
        Byte array representing a Linked Id from suitable
        commands.

 -> Return value (type integer):
        Linked Id.

-------------------------------------------------------------------------------

>>> ?TcapByteArrayToOperation

Convert a byte array to an Operation (as integer).

<integer> TcapByteArrayToOperation(<byte array>):

 -> Argument #0 (type byte array):
        Byte array representing an Operation from suitable
        commands.

 -> Return value (type integer):
        Operation.

-------------------------------------------------------------------------------

>>> ?TcapByteArrayToPointCode

Convert a byte array to a Point Code (as integer).

<integer> TcapByteArrayToPointCode(<byte array>):

 -> Argument #0 (type byte array):
        Byte array representing a Point Code from suitable
        commands.

 -> Return value (type integer):
        Point Code.

-------------------------------------------------------------------------------

>>> ?TcapByteArrayToQualityOfService

Convert a byte array to an Invoke Id (as integer).

<none> TcapByteArrayToQualityOfService(
                                    <byte array>,
                                    <integer>,
                                    <integer>,
                                    <integer>):

 -> Argument #0 (type byte array):
        Byte array representing a Quality of Service from
        suitable commands.

 -> Argument #1 (type integer):
        QOS Indicator (out).

 -> Argument #2 (type integer):
        QOS SLS Key (out).

 -> Argument #3 (type integer):
        QOS Priority (out).

-------------------------------------------------------------------------------

>>> ?TcapByteArrayToSccpAddress

Convert a SCCP Address to a byte array.

<none> TcapByteArrayToSccpAddress(
                            <byte array>,
                            <integer>,
                            <integer>,
                            <integer>,
                            <byte array>):

 -> Argument #0 (type integer):
        Sccp Address.

 -> Argument #1 (type integer):
        Point Code out).

 -> Argument #2 (type integer):
        SSN (out).

 -> Argument #3 (type byte array):
        GTT Information (out).

-------------------------------------------------------------------------------

>>> ?TcapDisassembleBeginDialogue

Disassemble a Begin Dialogue (from a byte array). Only the
parameters relevant to an indication can be retrieved.

<none> TcapDisassembleBeginDialogue(
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <boolean>):

 -> Argument #0 (type byte array):
        Begin Dialogue.

 -> Argument #1 (type byte array):
        Quality of Service (out).

 -> Argument #2 (type byte array):
        Application Context Name (out).

 -> Argument #3 (type byte array):
        User Information (out).

 -> Argument #4 (type byte array):
        Origination Address (out).

 -> Argument #5 (type byte array):
        Destination Address (out).

 -> Argument #6 (type byte array):
        Origination Point Code (out).

 -> Argument #7 (type byte array):
        Destination Point Code (out).

 -> Argument #8 (type boolean):
        Component Present (out).

-------------------------------------------------------------------------------

>>> ?TcapDisassembleEndDialogue

Disassemble an End Dialogue (from a byte array). Only the
parameters relevant to an indication can be retrieved.

<none> TcapDisassembleEndDialogue(
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <boolean>):

 -> Argument #0 (type byte array):
        End Dialogue.

 -> Argument #1 (type byte array):
        Quality of Service (out).

 -> Argument #2 (type byte array):
        Application Context Name (out).

 -> Argument #3 (type byte array):
        User Information (out).

 -> Argument #4 (type boolean):
        Component Present (out).

-------------------------------------------------------------------------------

>>> ?TcapDisassembleInvokeComponent

Disassemble an Invoke Component (from a byte array). Only
the operation class and the parameters relevant to an
indication can be retrieved.

<none> TcapDisassembleInvokeComponent(
                            <byte array>,
                            <integer>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <boolean>):

 -> Argument #0 (type byte array):
        Invoke Component.

 -> Argument #1 (type integer):
        Operation Class (out).

 -> Argument #2 (type byte array):
        Invoke Id (out).

 -> Argument #3 (type byte array):
        Linked Id (out).

 -> Argument #4 (type byte array):
        Operation (out).

 -> Argument #5 (type byte array):
        Parameters (out).

 -> Argument #6 (type boolean):
        Last Component (out).

-------------------------------------------------------------------------------

>>> ?TcapDisassembleResultLastComponent

Disassemble a Result Last Component (from a byte array).
Only the parameters relevant to an indication can be
retrieved.

<none> TcapDisassembleResultLastComponent(
                            <byte array>,
                            <byte array>,
                            <byte array>,
                            <boolean>):

 -> Argument #0 (type byte array):
        Result Last Component.

 -> Argument #1 (type byte array):
        Invoke Id (out).

 -> Argument #2 (type byte array):
        Operation (out).

 -> Argument #3 (type byte array):
        Parameters (out).

 -> Argument #4 (type boolean):
        Last Component (out).

-------------------------------------------------------------------------------

>>> ?TcapGetComponentType

Get Component type.

<integer> GetComponentType(<byte array>):

 -> Argument #0 (type byte array):
        Component.

 -> Return value (type integer):
        Component type.

-------------------------------------------------------------------------------

>>> ?TcapGetDialogueType

Get Dialogue type.

<integer> GetDialogueType(<byte array>):

 -> Argument #0 (type byte array):
        Dialogue.

 -> Return value (type integer):
        Dialogue type.

-------------------------------------------------------------------------------

>>> ?TcapGetNextEvent

Get next Event (blocking call).

<integer> GetNextEvent(<byte array>):

 -> Argument #0 (type byte array):
        Event (out).

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapInitialize

No description available for command TcapInitialize.

-------------------------------------------------------------------------------

>>> ?TcapInvokeIdToByteArray

Convert an Invoke Id (as integer) to a byte array.

<byte array> TcapInvokeIdToByteArray(<integer>):

 -> Argument #0 (type integer):
        Invoke Id.

 -> Return value (type byte array):
        Byte array representing an Invoke Id for suitable
        commands.

-------------------------------------------------------------------------------

>>> ?TcapIsComponentEvent

Is Component Event?

<boolean> IsComponentEvent(<byte array>):

 -> Argument #0 (type byte array):
        Event.

 -> Return value (type boolean):
        True if component, false if not component.

-------------------------------------------------------------------------------

>>> ?TcapIsDialogueEvent

Is Dialogue Event?

<boolean> IsDialogueEvent(<byte array>):

 -> Argument #0 (type byte array):
        Event.

 -> Return value (type boolean):
        True if component, false if not component.

-------------------------------------------------------------------------------

>>> ?TcapLinkedIdToByteArray

Convert a Linked Id (as integer) to a byte array.

<byte array> TcapLinkedIdToByteArray(<integer>):

 -> Argument #0 (type integer):
        Linked Id.

 -> Return value (type byte array):
        Byte array representing a Linked Id for suitable
        commands.

-------------------------------------------------------------------------------

>>> ?TcapOperationToByteArray

Convert an Operation (as integer) to a byte array.

<byte array> TcapOperationToByteArray(<integer>):

 -> Argument #0 (type integer):
        Operation.

 -> Return value (type byte array):
        Byte array representing an Operation for suitable
        commands.

-------------------------------------------------------------------------------

>>> ?TcapPeekNextEvent

Peek next Event (non-blocking call).

<integer> PeekNextEvent(<byte array>):

 -> Argument #0 (type byte array):
        Event (out).

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapPointCodeToByteArray

Convert a Point Code (as integer) to a byte array.

<byte array> TcapPointCodeToByteArray(<integer>):

 -> Argument #0 (type integer):
        Point Code.

 -> Return value (type byte array):
        Byte array representing a Point Code for suitable
        commands.

-------------------------------------------------------------------------------

>>> ?TcapPrintAddress

Print an Address (defined by a byte array).

<none> TcapPrintAddress(<byte array>):

 -> Argument #0 (type byte array):
        Address.

-------------------------------------------------------------------------------

>>> ?TcapPrintComponent

Print a Component (defined by a byte array).

<none> TcapPrintComponent(<integer>, <byte array>):

 -> Argument #0 (type integer):
        Dialogue Id.

 -> Argument #1 (type byte array):
        Component.

-------------------------------------------------------------------------------

>>> ?TcapPrintDialogue

Print a Dialogue (defined by a byte array).

<none> TcapPrintDialogue(<integer>, <byte array>):

 -> Argument #0 (type integer):
        Dialogue Id.

 -> Argument #1 (type byte array):
        Dialogue.

-------------------------------------------------------------------------------

>>> ?TcapQualityOfServiceToByteArray

Convert Quality of Service to a byte array.

<byte array> TcapQualityOfServiceToByteArray(
                                        <integer>,
                                        <integer>,
                                        <integer>):

 -> Argument #0 (type integer):
        QOS Indicator.

 -> Argument #1 (type integer):
        QOS SLS Key.

 -> Argument #2 (type integer):
        QOS Priority.

 -> Return value (type byte array):
        Byte array representing a Quality of Service for
        suitable commands.

-------------------------------------------------------------------------------

>>> ?TcapReceiveComponent

Receive a Component (from an Event).

<integer> TcapReceiveComponent(
                            <byte array>,
                            <integer>,
                            <byte array>):

 -> Argument #0 (type byte array):
        Event.

 -> Argument #1 (type integer):
        Dialogue Id (out).

 -> Argument #2 (type byte array):
        Component (out).

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapReceiveDialogue

Receive a Dialogue (from an Event).

<integer> TcapReceiveDialogue(
                            <byte array>,
                            <integer>,
                            <byte array>):

 -> Argument #0 (type byte array):
        Event.

 -> Argument #1 (type integer):
        Dialogue Id (out).

 -> Argument #2 (type byte array):
        Dialogue (out).

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapSccpAddressToByteArray

Convert a SCCP Address to a byte array.

<byte array> TcapSccpAddressToByteArray(
                                    <integer>,
                                    <integer>,
                                    <integer>,
                                    <byte array>):

 -> Argument #0 (type integer):
        Address Indicator.

 -> Argument #1 (type integer):
        Point Code.

 -> Argument #2 (type integer):
        SSN.

 -> Argument #3 (type byte array):
        GTT Information.

 -> Return value (type byte array):
        Byte array representing a SCCP Address for suitable
        commands.

-------------------------------------------------------------------------------

>>> ?TcapSendComponent

Send a Component.

<integer> TcapSendComponent(<integer>, <byte array>):

 -> Argument #0 (type integer):
        Dialogue Id.

 -> Argument #1 (type byte array):
        Component.

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapSendDialogue

Send a Dialogue.

<integer> TcapSendDialogue(<integer>, <byte array>):

 -> Argument #0 (type integer):
        Dialogue Id.

 -> Argument #1 (type byte array):
        Dialogue.

 -> Return value (type integer):
        Result (zero if success, negative value if failure).

-------------------------------------------------------------------------------

>>> ?TcapTerminate

No description available for command TcapTerminate.

-------------------------------------------------------------------------------

