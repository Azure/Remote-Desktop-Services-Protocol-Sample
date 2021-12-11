# Remote Desktop Services Protocol Sample


> This repro is in initial stages and open to feedback.

Windows natively provides support for "Remote Connections" via the [Remote Desktop Protocol Provider API](https://docs.microsoft.com/en-us/windows/win32/termserv/custom-remote-desktop-protocols). This API is rather complex, so this repository aims to provide the basic structure for someone to develop their own Remote Desktop Protocol Provider using the Remote desktop Services API. 

Although the name can be misleading, this API allows a developer to hook up their own remote input/output devices to a Windows Session. It expects the developer to provide everything else including the network protocol itself. This does not leverage the RDP protocol itself.

In this example we'll be covering APIs that are used after [19H1](https://en.wikipedia.org/wiki/Windows_10_version_1903), although these interfaces have been around since Windows Server 2008 R2 or earlier. In particular we'll be leveraging the new interfaces for [Indirect Display Drivers](https://docs.microsoft.com/en-us/windows-hardware/drivers/display/indirect-display-driver-model-overview).

One key note is that these samples will **not** be covering how to license windows sessions. Generally speaking, Windows 10 Client SKUs support only one active session at a time. If your use case would like to involve more than one active session consider using [Windows 10 Enterprise Multi-Session](https://docs.microsoft.com/en-us/azure/virtual-desktop/windows-10-multisession-faq) or Windows Server with the [Remote Desktop Session Host role](https://docs.microsoft.com/en-us/windows-server/remote/remote-desktop-services/rds-roles) installed. For further information about Windows Server licensing please see [Client Access Licenses](https://www.microsoft.com/en-us/licensing/product-licensing/client-access-license).

//TODO: Add link to tutorial.md

## Relevant MSDN documentation
Indirect Display Driver:
- [Overview](https://docs.microsoft.com/en-us/windows-hardware/drivers/display/indirect-display-driver-model-overview)
- [Sample](https://docs.microsoft.com/en-us/samples/microsoft/windows-driver-samples/indirect-display-driver-sample/)

Remote Desktop Protocol Provider API:
- [Overview](https://docs.microsoft.com/en-us/windows/win32/termserv/custom-remote-desktop-protocols)
- [Creating the provider](https://docs.microsoft.com/en-us/windows/win32/termserv/creating-a-custom-remote-protocol)
- [Sequence diagrams (Start/Connection/Reconnect)](https://docs.microsoft.com/en-us/windows/win32/termserv/method-call-sequence)
- [Registering the provider](https://docs.microsoft.com/en-us/windows/win32/termserv/registering-the-custom-protocol)
- [COM Interfaces](https://docs.microsoft.com/en-us/windows/win32/termserv/custom-remote-protocol-interfaces)

## Credit

Huge Credit to Kavya Lakhminarayanan (https://github.com/kavyaln2k) who wrote most (if not all) of this implementation.

## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.


## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft trademarks or logos is subject to and must follow 
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.
