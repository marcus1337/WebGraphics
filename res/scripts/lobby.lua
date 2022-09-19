
titleText = TitleText:new { textStr = "Lobby" }
setUIElements { MiniButtonPanel:new{hasCancel = true, hasSettings = true} }

team2seat1 = Seat:new {team = 2, x = 1110, y = 200, role = "Goalie"}
team2seat2 = Seat:new {team = 2, x = 1110, y = 400, role = "Defender"}
team2seat3 = Seat:new {team = 2, x = 1110, y = 600, role = "Attacker"}

team1seat1 = Seat:new {team = 1, x = 100, y = 200, role = "Goalie"}
team1seat2 = Seat:new {team = 1, x = 100, y = 400, role = "Defender"}
team1seat3 = Seat:new {team = 1, x = 100, y = 600, role = "Attacker"}

function update()
    updateUIElements()
    team2seat1:update()
    team2seat2:update()
    team2seat3:update()

    team1seat1:update()
    team1seat2:update()
    team1seat3:update()
end

function render()
    renderUIElements()
    titleText:render()
    team2seat1:render()
    team2seat2:render()
    team2seat3:render()

    team1seat1:render()
    team1seat2:render()
    team1seat3:render()
end
