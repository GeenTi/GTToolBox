Pod::Spec.new do |s|
  s.name             = "GTToolBox"
  s.version          = "1.2.1"
  s.summary          = "iOS App ToolBox"
  s.description  = <<-DESC 
                            GTToolBox
                    DESC
  s.homepage         = "https://github.com/GeenTi/GTToolBox"
  # s.screenshots      = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
  s.license          = 'MIT'
  s.author           = { "GeenTi" => "dev@geenti.com" }
  s.source           = { :git => "https://github.com/GeenTi/GTToolBox.git", :tag => s.version }
  # s.social_media_url = 'https://twitter.com/NAME'

  s.platform     = :ios
  s.ios.deployment_target = '12.0'
  s.osx.deployment_target = '11.0'

  s.source_files = 'GTToolBox/**/*.{h,m,mm,c}'
  s.public_header_files = 'GTToolBox/**/*.h'   #公开头文件地址
  s.frameworks = 'UIKit','Foundation','libc','SystemConfiguration','CFNetwork','CoreGraphics','QuartzCore'
  s.pod_target_xcconfig = { 'VALID_ARCHS' => 'x86_64 armv7 arm64' }
end
