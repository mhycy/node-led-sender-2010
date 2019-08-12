{
  "targets": [
    {
      "target_name": "LEDSender2010",
      "sources": [ "src/wrapper.cc" ],
      'conditions': [
        ['OS=="win"', {
            'copies': [{
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'third_party/LEDSender2010.dll',
                'third_party/Lzss.dll'
              ]
            }],
            'include_dirs': [
              'third_party/include'
            ]
        }]
      ]
    },
    {
      "target_name": "demo",
      "sources": [ "src/demo.cc" ]
    }
  ]
}