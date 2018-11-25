import print_inline as pin
import filter_quantize as fq
import curve
import json_service

quantimg = fq.filterQuantize("images/fruit.jpg")
quants = fq.splitQuantize(quantimg, 8)

for quant in quants:
	pin.printInline(quant)

data = json_service.bulkFormatJSON(curve.curves)
json_service.writeJSONtoFile("fruit_inline.json", data)