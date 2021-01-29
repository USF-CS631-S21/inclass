function onBufferOpen(b)
	local ft = b:FileType()

	if ft == "asm" then
--		if string.find(b:Line(0), "arm_asm") then
		b:SetOption("filetype", "arm_asm")
--		end
	end
end
