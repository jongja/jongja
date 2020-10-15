enum AppleOS{
    case iOS
    case macOS
    case tvOS
    case watchOS
}

var osType: AppleOS = .iOS

func printAppleDevice(osType: AppleOS){
    switch osType {
    case .iOS:
        print("iPhone")
    case .macOS:
        print("iMac")
    case .tvOS:
        print("Apple TV")
    case .watchOS:
        print("Apple watch")
    }
}

printAppleDevice(osType: .watchOS)
