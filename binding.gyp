{
  "targets": [
    {
      "target_name": "LEDSender2010Wrapper",
      "sources": [ "src/wrapper.cc" ],
      'conditions': [
        ['OS=="win"', {
            "libraries": [
              "../third_party/LEDSender2010.lib"
            ],
            'include_dirs': [
              'third_party/include'
            ],
            'copies': [{
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'third_party/LEDSender2010.dll',
                'third_party/Lzss.dll'
              ]
            }]
        }]
      ]
    },
    {
      "target_name": "test",
      "sources": [ "src/test.cc" ],
      'conditions': [
        ['OS=="win"', {
            "libraries": [
              "../third_party/LEDSender2010.lib"
            ],
            'include_dirs': [
              'third_party/include',
              'src/include'
            ],
            'copies': [{
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'third_party/LEDSender2010.dll',
                'third_party/Lzss.dll'
              ]
            }]
        }]
      ]
    }
  ]
}