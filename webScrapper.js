const puppeteer = require('puppeteer');

(async function main(){
    try{
    const browser = await puppeteer.launch({headless: false});
    const page = await browser.newPage();
    await page.goto('https://votesmart.org/');

    await page.waitFor('input[name=q]');
    await page.type('input[name=q]', 'Christopher Tracy');
    
    await page.waitFor(10000);
    
    await page.click('#folder-bio > div.front > span');
    await page.waitFor(10000);
    await page.click('#folder-bio > div.front > span');
    
    await page.waitForNavigation({waitUntil: 'networkidle2'})

    var data = {};
    data.table = [];

    const result = await page.evaluate(() => {
        let fullName   = document.querySelector('span[itemprop=gender]').innerText;

        return{
            fullName,
        }

    });
    var results = {
        "Name": result.fullName,
        "birthPlace": result.birthPlace
    }
    data.table.push(results);

    await page.click('#folder-finance > div.front > span');
    await page.waitForNavigation({waitUntil: 'networkidle2'})

    const finance = await page.evaluate(() => {
        let name1   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(1) > td.span-4').innerText;
        let donation1   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(1) > td.span-3.currency').innerText;
        let name2   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(2) > td.span-4').innerText;
        let donation2   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(2) > td.span-3.currency').innerText;
        let name3   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(3) > td.span-4').innerText;
        let donation3   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(3) > td.span-3.currency').innerText;
        let name4   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(4) > td.span-4').innerText;
        let donation4   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(4) > td.span-3.currency').innerText;
        let name5   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(5) > td.span-4').innerText;
        let donation5   = document.querySelector('#main > section > div.main.clear > div > div:nth-child(4) > div.border-top-1.clearfix.section.span-8 > div > table > tbody > tr:nth-child(5) > td.span-3.currency').innerText;
        
        return{
            name1,
            donation1,
            name2,
            donation2,
            name3,
            donation3,
            name4,
            donation4,
            name5,
            donation5
        }
    });

    var finances = {
        "TopContributer": finance.name1,
        "Donation1": finance.donation1,
        "Contributer2": finance.name2,
        "Donation2": finance.donation2,
        "Contributer3": finance.name3,
        "Donation3": finance.donation3,
        "Contributer4": finance.name4,
        "Donation4": finance.donation4,
        "Contributer5": finance.name5,
        "Donation5": finance.donation5
    }
    data.table.push(finances);

    await page.click('#folder-rating > div.front');
    await page.waitForNavigation({waitUntil: 'networkidle2'})

    const rating = await page.evaluate(() => {
        let organization   = document.querySelector('#main > section > div.main.clear > div > div.section.content_float > div.issues > table > tbody > tr > td:nth-child(2) > a').innerText;
        let rating     = document.querySelector('#main > section > div.main.clear > div > div.section.content_float > div.issues > table > tbody > tr > td:nth-child(3)').innerText; 

        return{
            organization,
            rating,
        }

    });

    browser.close();

    var json = JSON.stringify(data);
    var json1 = JSON.parse(json);

    //var json = JSON.stringify(obj);
    //console.log(obj.fullName);
    //console.log(obj.birthPlace);
    //console.log(json);
    //console.log(json);
    console.log(json1);
    //console.log(rating);

    var fs = require('fs');
    fs.writeFile("test.txt", json, function(err) {
        if (err) {
            console.log(err);
        }
    });

    return result;
}catch(e){}}
)();

//Matt Boehnke