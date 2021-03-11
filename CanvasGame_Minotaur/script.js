window.onload=function(){//onload je zato ker včasih ni naložilo slike for one reason or another
                         //now it works every time

    //dobim sliko iz main in potem narišem na canvas
    const imgPlayer= document.getElementById("myImage");
    const imgArrow= document.getElementById("myArrow");
    const img1Up= document.getElementById("my1Up");
    const imgXtraDmg= document.getElementById("myXtraDmg");
    const imgEnemy =document.getElementById("myHarpy");
    const imgBackground= document.getElementById("myBackground");
    const imgScroll=document.getElementById("myScroll");

    const scrollbox=document.getElementById("scrollbox");

    const strtbtn=document.getElementsByClassName("buttonlook");

    const optionbtn=document.getElementsByClassName("buttonlook");

    const Backbut=document.getElementsByClassName("buttonlook");

    const modal=document.getElementsByClassName("bg-white");
    const Optionsmodal=document.getElementsByClassName("option-white");
    const PauseOptionsmodal=document.getElementsByClassName("option-white");
    const modalScore=document.getElementById("modalScore");

    const scoreNum=document.getElementById("scoreNum");
    const healthNum=document.getElementById("healthNum");
    const dmgNum=document.getElementById("dmgNum");
    const leftbuttonpres=document.getElementById("leftbutton");
    const rightbuttonpres=document.getElementById("rightbutton");

    const reassingbutton=document.getElementsByClassName("buttonlookres");

    const VolumeSlider=document.getElementsByClassName("volume_slider");

    const canvas=document.querySelector('canvas');

    const ctx=canvas.getContext('2d');

    canvas.height=innerHeight;
    canvas.width=innerWidth;
    modalScore.innerHTML=localStorage.getItem("highscore");

    let Music=new Audio('Glorious_morning.mp3');
    Music.loop=true;
let rotation=0;
let state=0;
let enemystater=0;
let enemystatel=4;
let leftkey="KeyA";
let rightkey="KeyD";

// CLASS DEFINITIONS
class Player
{
    constructor(x,y,sizex,sizey,rotation,img)
    {
        this.x=x;
        this.y=y;
        this.sizex=sizex;
        this.sizey=sizey;
        this.img=img;
        this.diagonala=Math.sqrt(Math.pow(this.sizex,2)+Math.pow(this.sizey,2));
        this.health=1;
        this.rotation=rotation;
        this.damage=1;
    }

    draw()
    {
        ctx.drawImage(this.img,
            state*this.sizex,
            0,
            this.sizex,
            this.sizey,
            this.x,
            this.y,
            this.sizex,
            this.sizey,
            ); //riše player
        ctx.stroke();
    }
};


class Arrow
{
    constructor(x,y,sizeX,sizeY,speed,rotation)
    {
        this.x=x;
        this.y=y;
        this.sizeX=sizeX;
        this.sizeY=sizeY
        this.speed=speed;
        this.rotation=rotation;
    }

    draw()
    {
        ctx.drawImage(imgArrow,this.x,this.y,this.sizeX,this.sizeY); //riše Arrow
        ctx.stroke();
    }

    update(){
        this.draw();
        this.x=this.x+this.speed.x;
        this.y=this.y+this.speed.y;
    }
};

class Enemy
{
    constructor(x,y,sizeX,sizeY,speed,state,droppable)
    {
        this.x=x;
        this.y=y;
        this.sizeX=sizeX;
        this.sizeY=sizeY
        this.speed=speed;
        this.health=Math.floor(Math.random()*4)
        this.state=state;
        this.droppable=droppable;
    }

    draw()
    {   
        ctx.drawImage(imgEnemy,
            this.state*this.sizeX,
            0,
            this.sizeX,
            this.sizeY,
            this.x,
            this.y,
            this.sizeX,
            this.sizeY); //riše Enemy
        ctx.stroke();
    }

    update(){
        this.draw();
        this.x=this.x+this.speed.x;
        this.y=this.y+this.speed.y;
    }

    checkPlayerpos(newSpeed){
        this.speed=newSpeed;
    }
};

class Particle
{
    constructor(x,y,radius,color,speed)
    {
        this.x=x;
        this.y=y;
        this.radius=radius;
        this.color=color;
        this.speed=speed;
        this.alpha=1
    }

    draw()
    {   
        ctx.save();
        ctx.globalAlpha=this.alpha;
        ctx.beginPath();
        ctx.arc(this.x,this.y,this.radius,0,Math.PI*2,false)//riše particle
        ctx.fillStyle=this.color;
        ctx.fill();
        ctx.stroke();
        ctx.restore();
    }

    update(){
        this.draw();
        this.x=this.x+this.speed.x;
        this.y=this.y+this.speed.y;
        this.alpha-=0.01;
    }
};

class Upgrade
{
    constructor(x,y,sizeX,sizeY,ID,img)
    {
        this.x=x;
        this.y=y;
        this.sizeX=sizeX;
        this.sizeY=sizeY;
        this.ID=ID;
        this.img=img;
    }

    draw()
    {
        ctx.drawImage(this.img,this.x,this.y,this.sizeX,this.sizeY); //riše Upgrade
        ctx.stroke();
    }

    update(){
        this.draw();
        if(this.y<=canvas.height/1.15)
        {
            this.y+=4;
        }
    }
}

//pozicija PlayerSprite
const StartingX= canvas.width/2;
const StartingY=canvas.height/1.25;

let player=new Player(StartingX,StartingY,100,100,0,imgPlayer);
let arrows=[];
let enemies=[];
let particles=[];
let upgrades=[];



ctx.drawImage(imgScroll,canvas.width/3.4,canvas.height/4,800,600);
function inicializacija(){
    player=new Player(StartingX,StartingY,100,100,0,imgPlayer);
    arrows=[];
    enemies=[];
    particles=[];
    upgrades=[];
    score=0;
    healthNum.innerHTML=player.health;
    scoreNum.innerHTML=score;
    dmgNum.innerHTML=player.damage;
    modalScore.innerHTML=localStorage.getItem("highscore");
    Music.play();

};
let dropstate=0;
function spawnEnemies()
{
    setInterval(function(){
        dropstate=Math.floor(Math.random()*2);
        const sizeX=50;
        const sizeY=50;
        let x=Math.random() < 0.5 ? 0-sizeX : canvas.width+sizeX;
        let y=Math.random()*canvas.height/1.5;
        const angle=Math.atan2(player.y-y,player.x-x);
        //smer potovanja
        const speed={
            x: Math.cos(angle),
            y: Math.sin(angle)
        }
        if(x==canvas.width+sizeX)
        {
            enemies.push(new Enemy(x,y,sizeX,sizeY,speed,enemystater,dropstate));
        }
        if(x==0-sizeX)
        {
            enemies.push(new Enemy(x,y,sizeX,sizeY,speed,enemystatel,dropstate));
        }
        
    },2000);
};


let animationId;
let score=0;

let UpgradeTime=0;
//timer za strelanje
let timer=60;
//frame za sprites
let frame=0;
let enemyframe=0;
//animira vse
function animate()
{
    canvas.height=innerHeight;
    canvas.width=innerWidth;
    animationId=requestAnimationFrame(animate); // starta animation
    ctx.drawImage(imgBackground,0,0,canvas.width,canvas.height);
    player.y=canvas.height/1.25;
    player.draw();
    timer--;
    frame++;
    enemyframe++;
    UpgradeTime--;
    
    if(UpgradeTime==0)
    {
        console.log(player.damage);
        player.damage=1;
        dmgNum.innerHTML=player.damage;
    }

    if(UpgradeTime<0) UpgradeTime=-1;

    upgrades.forEach((upgrade,upgradeIndex)=>{
        upgrade.update();
        const razdalja=Math.hypot(player.x-upgrade.x,player.y-upgrade.y);
        if(player.rotation==0)
        {
            console.log(razdalja-upgrade.sizeX);
            if(razdalja-upgrade.sizeX<=45)
            {
                if(upgrade.ID==1)
                {
                    player.health++;
                    healthNum.innerHTML=player.health;
                }
                if(upgrade.ID==2)
                {
                    player.damage=3;
                    dmgNum.innerHTML=player.damage;
                    UpgradeTime=500;
                }
                upgrades.splice(upgradeIndex, 1);
                upgrade.update();
            } 
        }
        else
        {
            if(player.rotation==1)
            {
                if(razdalja-upgrade.sizeX<=70)
                {
                    if(upgrade.ID==1)
                    {
                        player.health++;
                        healthNum.innerHTML=player.health;
                    }
                    if(upgrade.ID==2)
                    {
                        player.damage=3;
                        dmgNum.innerHTML=player.damage;
                        UpgradeTime=500;
                    }
                    upgrades.splice(upgradeIndex, 1);
                    upgrade.update();
                } 
            }
        }
    }
    )
        

    particles.forEach((particle,index)=>{
        if(particle.alpha<=0.01)
        {
            particles.splice(index,1)
        }else{
            particle.update();
        }
        
    })
    arrows.forEach((arrow,arrowIndex)=>{
        arrow.update();
        //briše arrows, ki grejo offscreen
        if(arrow.x+arrow.sizeX<0 || arrow.x-arrow.sizeX>canvas.width||
            arrow.y+arrow.sizeY<0||arrow.y-arrow.sizey>canvas.height)
            {
                setTimeout(()=>{
                    arrows.splice(arrowIndex, 1);
                },0
                ) 
            }
        }
    );

    // index zapisuje trenutni enemy, s tem lahko spliceam
    enemies.forEach((enemy, index)=>
    {
        //enemy position compared to ground(kill on contact)
        if(enemy.y>=canvas.height/1.25+30)
        {
            setTimeout(()=>{
                enemies.splice(index, 1);
                },0)
                //naredi particle explosion
                for(let i=0;i<10;i++)
                    {
                        particles.push(new Particle(enemy.x,enemy.y,Math.random()*2,"RGB(110,104,104)",
                        {   
                            x: (Math.random()-0.5)*30,
                            y: (Math.random()-0.5)*30
                        })
                        )
                    }
        }
        //update smer potovanja da te followa enemy
        const Newangle=Math.atan2(player.y+40-enemy.y,player.x-enemy.x);
        const Newspeed={
            x: Math.cos(Newangle),
            y: Math.sin(Newangle)
        }
        //update smer glede na player
        enemy.checkPlayerpos(Newspeed);
        
        //sprite animation
        if(enemyframe%10==0 && (enemies[index].x>player.x+player.sizex))
        {
           
            enemystater++;
            enemy.state=enemystater;
            if(enemystater>=3)
            {
                enemystater=0;
            }
            if(enemyframe==100) enemyframe=0;
            
        }
        if(enemyframe%10==0 && (enemies[index].x<player.x))
        {
            
            enemystatel++;
            enemy.state=enemystatel;
            if(enemystatel>=7)
            {
                enemystatel=4;
            }
            if(enemyframe==100) enemyframe=0;
        }
        enemy.update();

        //razdalja med player in enemy spet lahko razdalja ker je prva znotraj forEach
        const razdalja=Math.hypot(player.x+30-enemy.x,player.y+40-enemy.y);
        if(razdalja-enemy.sizeX-player.sizex<-80) //end game
        {
            player.health--;
            healthNum.innerHTML=player.health;
            enemies.splice(index,1);
            if(player.health==0)
            {
                Music.pause();
                Music.currentTime=0;
                cancelAnimationFrame(animationId);
                modalScore.innerHTML=localStorage.getItem("highscore");
                modal[0].style.display="block"; 
                ctx.drawImage(imgScroll,canvas.width/3.4,canvas.height/4,800,600);
            }
            
        }
        arrows.forEach((arrow, arrowIndex)=>{
            //razdalja med enemy in arrow
            const razdalja=Math.hypot(arrow.x-enemy.x-25,arrow.y-enemy.y);
            //dotik arrow in enemy
            if(razdalja-enemy.sizeX-arrow.sizeX<-20)
            {
                if(enemy.health>1)//added enemy HP, add coloring to go with
                {
                    enemy.health-=(player.damage);
                    if(enemy.health<1)
                    {
                        //naredi particle explosion
                    for(let i=0;i<10;i++)
                    {
                        particles.push(new Particle(arrow.x,arrow.y,Math.random()*2,"RGB(110,104,104)",
                        {   
                        x: (Math.random()-0.5)*30,
                        y: (Math.random()-0.5)*30}
                         )
                        )
                    }
                     //Upgrade drop
                    if(enemy.droppable==1)
                    {
                        let UpgradeID=Math.floor(Math.random()*4)
                        if(UpgradeID==1)
                            {
                                upgrades.push(new Upgrade(enemies[index].x,enemies[index].y,30,30,UpgradeID,img1Up));
                            }
                        if(UpgradeID==2)
                            {
                                upgrades.push(new Upgrade(enemies[index].x,enemies[index].y,30,30,UpgradeID,imgXtraDmg));
                            }
                    }

                    //Timeout prepreči enemy flashing on death(čaka do konca frame da začne brisati) 
                    setTimeout(()=>{
                    enemies.splice(index, 1);
                    arrows.splice(arrowIndex, 1);
                    },0)



                    //score povečan for 100
                    score+=100;

                    let highscore=localStorage.getItem("highscore");
                    if(highscore !== null)
                    {
                        if (score > highscore) 
                        {
                            localStorage.setItem("highscore", score);      
                        }
                    }
                    else
                    {
                        localStorage.setItem("highscore", score);
                    }
                    scoreNum.innerHTML=score;
                    }
                    setTimeout(()=>{
                        arrows.splice(arrowIndex, 1);
                    },0)
                    //score increase for 10
                    score+=10;
                    let highscore=localStorage.getItem("highscore");
                    if(highscore !== null)
                    {
                        if (score > highscore) 
                        {
                            localStorage.setItem("highscore", score);      
                        }
                    }
                    else
                    {
                        localStorage.setItem("highscore", score);
                    }
                    scoreNum.innerHTML=score;
                }
                else{
                    //naredi particle explosion
                    for(let i=0;i<10;i++)
                    {
                        particles.push(new Particle(arrow.x,arrow.y,Math.random()*2,"RGB(110,104,104)",
                        {   
                        x: (Math.random()-0.5)*30,
                        y: (Math.random()-0.5)*30}
                         )
                        )
                    }
                     //Upgrade drop
                    if(enemy.droppable==1)
                    {
                        let UpgradeID=Math.floor(Math.random()*4)
                        if(UpgradeID==1)
                            {
                                upgrades.push(new Upgrade(enemies[index].x,enemies[index].y,30,30,UpgradeID,img1Up));
                            }
                        if(UpgradeID==2)
                            {
                                upgrades.push(new Upgrade(enemies[index].x,enemies[index].y,30,30,UpgradeID,imgXtraDmg));
                            }
                    }

                    //Timeout prepreči enemy flashing on death(čaka do konca frame da začne brisati) 
                    setTimeout(()=>{
                    enemies.splice(index, 1);
                    arrows.splice(arrowIndex, 1);
                    },0)



                    //score povečan for 100
                    score+=100;

                    let highscore=localStorage.getItem("highscore");
                    if(highscore !== null)
                    {
                        if (score > highscore) 
                        {
                            localStorage.setItem("highscore", score);      
                        }
                    }
                    else
                    {
                        localStorage.setItem("highscore", score);
                    }
                    scoreNum.innerHTML=score;
                } 
            }
        })
    })
    
};

// premik player levo desno
document.addEventListener('keydown',(event)=>{
    if(event.code==leftkey)
    {
        player.x-=10;
        if(player.x<-10)
        {
            player.x=-10;
        }
        rotation=0;
        player.rotation=rotation;
        console.log(rotation);
        if(frame%3==0)
        {
            state++;
            if(state>=3)
            {
                state=0;
                frame=0;
            }
        }
    }
    if(event.code==rightkey)
    {
        player.x+=10;
        if(player.x>canvas.width-player.sizex+10)
        {
            player.x=canvas.width-player.sizex+10;
        }
        rotation=1;
        player.rotation=rotation;
        console.log(rotation);
        if(frame%3==0)
        {
            state++;
            if(state>=7)
            {
                state=4;
                frame=0;
            }
        }
    }
})

document.addEventListener('keyup',(event)=>{
    if(event.code==leftkey)
    {
        state=0;
        frame=0;
    }
    if(event.code==rightkey)
    {
        state=7;
        frame=0;
    }
})

//na klik izračuna kot od player do klika in izračuna hitrost za premik
//v arrows array pusha vsak now arrow in izrisuje
window.addEventListener('click',(event)=>{
    const angle=Math.atan2(event.clientY-player.y-30,event.clientX-player.x-100*rotation);
    const speed={
        x: Math.cos(angle)*7,
        y: Math.sin(angle)*7
        }
        if(timer<=0)
        {
            arrows.push(new Arrow(player.x+100*rotation,player.y+30,15,15,speed,)); //create arrow
            timer=60;
        }
        }
);

//GAME PAUSE



// BUTTON FOR START
strtbtn[0].addEventListener("click",()=>{
    inicializacija();
    animate();
    spawnEnemies();
    modal[0].style.display="none";
    frame=0;
});

//BUTTON FOR OPTIONS
optionbtn[1].addEventListener("click",()=>{
    Optionsmodal[0].style.display="block";
    modal[0].style.display="none";
    Music.play();
    ctx.drawImage(imgScroll,canvas.width/3.4,canvas.height/4,800,600);
    
    reassingbutton[0].addEventListener("keydown",(event)=>{
        leftkey=event.code;
        leftbuttonpres.innerHTML=event.code;
    })
    reassingbutton[1].addEventListener("keydown",(event2)=>{
        rightkey=event2.code;
        rightbuttonpres.innerHTML=event2.code;
    })

    //volume slider
    VolumeSlider[0].addEventListener("change",()=>{
        Music.volume=VolumeSlider[0].value/100;
        if(VolumeSlider[0].value/100==0.01)
        {
            Music.volume=0;
        }
    })
    
    //BACK BUTTON IN OPTIONS
    optionbtn[2].addEventListener("click",()=>{
        Optionsmodal[0].style.display="none";
        modal[0].style.display="block";
        Music.pause();
        Music.currentTime=0;
        optionbtn[2].removeEventListener;
    })
})
}